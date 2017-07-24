#include "../../Header/Interface/Animate.h"

Animate::Animate() {

}

Animate::~Animate() {

}

Animate::Timeline& Animate::getTimeline(std::string const& anim_name) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end())
        return anim->second;

    assert(false);
}

Animate::Timeline const& Animate::getTimeline(std::string const& anim_name) const {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end())
        return anim->second;

    assert(false);
}


void Animate::update(float _deltaTime) {
    for (auto& p : timelines) {
        Timeline& t = p.second;

        float deltaTime = _deltaTime * t.speed;
        float transitionTime = t.current_time;

        t.current_time += deltaTime;
        while (t.current_time >= t.baseTime)
            t.current_time -= t.baseTime;

        if (t.next != nullptr) {
            float timeBeforeNext = 0;
            differenceForward(t, transitionTime, t.next->time, timeBeforeNext);

            Animate::Callback* last_callback = nullptr;

            // while the next event can be reached
            while (timeBeforeNext <= deltaTime) {
                if (last_callback != nullptr) {
                    (*last_callback)(t.current_time, 0, 1);
                }
                last_callback = &t.current->callback;

                advanceTimelinePtrs(t);

                transitionTime += timeBeforeNext;
                if (transitionTime >= t.baseTime) transitionTime -= t.baseTime;

                deltaTime -= timeBeforeNext;

                differenceForward(t, transitionTime, t.next->time, timeBeforeNext);
            }

            differenceForward(t, t.current_time, t.next->time, timeBeforeNext);
            if (last_callback != nullptr && *last_callback != nullptr) {
                (*last_callback)(t.current_time, timeBeforeNext, getProgress(t));
            }
        }
    }
}

void Animate::createAnimation(std::string const& name) {
    timelines[name] = {};
}

void Animate::createEvent(std::string const& anim_name, float time, Callback const& callback) {
    insertEvent(getTimeline(anim_name), callback, time);
}

float Animate::getAnimationTime(std::string const& anim_name) const {
    return getTimeline(anim_name).current_time;
}

float Animate::getProgress(std::string const& anim_name) const {
    return getProgress(getTimeline(anim_name));
}

float Animate::getProgress(Timeline const& t) const {
    if (t.next == nullptr || t.current == nullptr)
        return -1;

    float diff = 0;
    float diffMax = 0;

    auto* next = t.next;
    if (t.repeat && (next == t.first || next == t.first->prev))
        next = t.first->next;

    auto* current = t.current;
    if (t.repeat && (current == t.first || current == t.first->prev))
        current = t.first->prev->prev;

    if (differenceForward(t, current->time, next->time, diffMax)) {
        if (differenceForward(t, t.current_time, next->time, diff)) {
            if (diffMax == 0 || diffMax < diff) {
                std::cout << "Diff between " << current->time << " and " << next->time << " : " << diffMax <<  std::endl;
                std::cout << "Diff between " << t.current_time << " and " << next->time << " : " << diffMax <<  std::endl;
                assert(false);
            }
            assert(diffMax != 0);
            return (diffMax - diff) / diffMax;
        }
    }
    return -1;
}

float Animate::getTimeBeforeNextEvent(std::string const& anim_name) const {
    return getTimeBeforeNextEvent(getTimeline(anim_name));
}

float Animate::getTimeBeforeNextEvent(Timeline const& t) const {
    if (t.next == nullptr)
        return -1;

    float diff = 0;
    auto* next = t.next;
    if (t.repeat && (next == t.first || next == t.first->prev))
        next = t.first->next;

    if (differenceForward(t, t.current_time, next->time, diff)) {
        return diff;
    }
    return -1;
}

void Animate::setSpeed (std::string const& anim_name, float speed) {
    assert(speed > 0);
    getTimeline(anim_name).speed = speed;
}

void Animate::setRepeated(std::string const& anim_name, bool repeat, float baseTime) {
    assert(baseTime > 0);
    auto& t = getTimeline(anim_name);
    if (repeat == t.repeat) { // just to modify baseTime
        if (t.baseTime != baseTime && t.first != nullptr) {
            t.first->prev->time = baseTime;
            t.baseTime = baseTime;
        }
        return;
    }

    if (repeat) { // non-repeating to repeating
        if (t.first != nullptr) {
            
            // We have : nullptr <- e_0 <-> e_1 <-> ... <-> e_n -> nullptr
            // to turn into : (last) <-- first <-> e_0 <-> e_1 <-> e_2 <-> ... <-> e_n <-> last --> (first)

            // Create first and last
            auto first = new EventList(nullptr, 0);
            first->is_first = true;

            auto last = new EventList(nullptr, baseTime);
            last->is_last = true;

            // loop : first <-> last
            last->next = first;
            first->prev = last;

            // find e_0
            auto* e_0 = t.first;

            // first <-> e_0
            first->next = e_0;
            e_0->prev = first;

            // find e_n
            auto* e_n = t.first;
            while (e_n->next != nullptr)
                e_n = e_n->next;

            // e_n <-> last
            e_n->next = last;
            last->prev = e_n;

            if (last->prev->time >= last->time) {
                // We have : (last) <-- first <-> e_0 <-> ... <-> e_n <-> last --> (first)
                // to turn into : (last) <-- first <-> e_0 <-> ... <-> e_x_min     <->     last --> (first)
                //                                                        ^-- e_x <-> ... --^

                // Finding e_x_min
                auto* e_x_min = last;
                while (e_x_min->time >= last->time)
                    e_x_min = e_x_min->prev;

                // Finding e_x
                auto* e_x = e_x_min->next;

                // e_x_min <-> last
                e_x_min->next = last;
                last->prev = e_x_min;

                // delete all e_x
                while (e_x != last) {
                    auto* to_delete = e_x;
                    e_x = e_x->next;
                    delete to_delete;
                }
            }

            // timeline pointers
            t.first = first;
            recalculatePointers(t);
        }
    } else {
        if (t.first != nullptr) {
            // We have : (last) <-- first <-> e_0 <-> e_1 <-> e_2 <-> ... <-> e_n <-> last --> (first)
            // to turn into : nullptr <- e_0 <-> e_1 <-> ... <-> e_n -> nullptr

            // find e_0, e_n, first and last
            auto* first = t.first;
            auto* last = first->prev;
            auto* e_0 = first->next;
            auto* e_n = last->prev;

            // make e_0 and e_n pointing towards nullptr
            e_0->prev = nullptr;
            e_n->next = nullptr;

            // clean
            delete first;
            delete last;

            // timeline pointers
            t.first = e_0;
            recalculatePointers(t);
        }
    }

    t.repeat = repeat;
    t.baseTime = baseTime;
}

void Animate::advanceTimelinePtrs (Timeline& t) {
    if (t.next != nullptr) {
        t.current = t.next;
        if (t.repeat && t.next->next == t.first->prev) {
            t.next = t.first->next;
        } else {
            t.next = t.next->next;
        }
    }
}

bool Animate::differenceForward(Timeline const& t, float time0, float time1, float& result) const {
    if (time0 < time1) {
        result = time1 - time0;
        return true;
    }
    if (t.repeat) {
        result = t.baseTime - time0 + time1;
        return true;
    }

    return false;
}

bool Animate::differenceBackward(Timeline const& t, float time0, float time1, float& result) const {
    return differenceForward(t, time1, time0, result);
}

void Animate::insertEvent(Timeline& t, Callback const& callback, float time) {
    if (t.baseTime <= time)
        return;

    auto* e = new EventList(callback, time);

    if (t.first == nullptr) { // First element added
        if (t.repeat) {
            // We have : nullptr
            // We want : (last) <-- first <-> e <-> last --> (first)

            // Creation of first and last
            auto* first = new EventList(nullptr, 0);
            auto* last = new EventList(nullptr, t.baseTime);

            // loop = is_true / is_false
            first->is_first = true;
            last->is_last = true;

            // last <-> first
            last->next = first;
            first->prev = last;

            // first <-> e
            first->next = e;
            e->prev = first;

            // e <-> last
            e->next = last;
            last->prev = e;

            // timeline pointers
            t.first = first;
        } else {
            // We have : nullptr
            // We want : nullptr <-> e <-> nullptr

            // timeline pointers
            t.first = e;
        }
    } else { // List is not empty
        if (t.repeat) {
            // We have : (last) <-- first <-> ... <-> e_p <-> e_n <-> ... <-> last --> (first)
            // We want : (last) <-- first <-> ... <-> e_p <-> e <-> e_n <-> ... <-> last --> (first)

            // Finding e_n
            auto* e_n = t.first;
            while (e_n->time <= time) {
                e_n = e_n->next; 
            }

            // Finding e_p
            auto* e_p = e_n->prev;

            // e_p <-> e
            e_p->next = e;
            e->prev = e_p;

            // e <-> e_n
            e->next = e_n;
            e_n->prev = e;

            // timeline pointers
        } else {
            // We have : nullptr <-- ... <-> e_p <-> e_n <-> ... --> nullptr
            // We want : nullptr <-- ... <-> e_p <-> e <-> e_n <-> ... --> nullptr

            // or

            // We have : nullptr <-- ... <-> e_p --> nullptr
            // We want : nullptr <-- ... <-> e_p <-> e --> nullptr

            // or

            // We have : nullptr <-- e_n <-> ... --> nullptr
            // We want : nullptr <-- e <-> e_n <-> ... --> nullptr

            // Case 3 ?
            if (t.first->time > time) {
                // Finding e_n
                auto* e_n = t.first;

                // e <-> e_n
                e->next = e_n;
                e_n->prev = e;

                // timeline pointers
                t.first = e;
            } else {
                // Finding e_n and e_p
                auto* e_p = t.first;
                auto* e_n = t.first->next;
                while (e_n != nullptr && e_n->time <= time) {
                    e_p = e_n;
                    e_n = e_n->next; 
                }
                assert(e_p != nullptr && e_p->next == e_n);

                // e_p <-> e
                e_p->next = e;
                e->prev = e_p;

                // Case 1 ?
                if (e_n != nullptr) {
                    // e <-> e_n
                    e->next = e_n;
                    e_n->prev = e;
                }
            }
        }
    }
    recalculatePointers(t);
}

Animate::Timeline::~Timeline() {
    auto* cur = first;
    while (cur != nullptr) {
        if (cur->is_last) {
            delete cur;
            break;
        }
        auto* to_delete = cur;
        cur = cur->next;
        delete to_delete;
    }
}

void Animate::recalculatePointers(Timeline& t) {
    if (t.repeat) {
        // put current_time in interval [0; baseTime[
        while (t.current_time >= t.baseTime)
            t.current_time -= t.baseTime;
    }

    if (t.first == nullptr) {
        t.next = t.current = nullptr;
        return;
    }

    // Find cur and next
    auto* cur = t.first;
    auto* next = cur->next;
    while (next != nullptr && next->time <= t.current_time) {
        cur = next;
        next = next->next; 
    }

    assert(cur != nullptr);
    if (t.repeat) {
        assert(next != nullptr);

        if (next == t.first || next == t.first->prev)
            next = t.first->next;

        if (cur == t.first || cur == t.first->prev)
            cur = t.first->prev->prev;
    }
    t.current = cur;
    t.next = next;
}