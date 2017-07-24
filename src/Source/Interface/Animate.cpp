#include "../../Header/Interface/Animate.h"

Animate::Animate() {

}

Animate::~Animate() {

}

void Animate::update(float deltaTime) {
    for (auto& p : timelines) {
        Timeline& t = p.second;
        if (t.nextEvent == t.events.end()) {
            t.current_time += deltaTime;
        } else {
            float progressTime = getProgressBeforeNextEvent(p.first);
            std::cout << "Current : " << t.current_time << std::endl;
            std::cout << "deltaTime : " << deltaTime << std::endl;
            std::cout << "Progress : " << progressTime << std::endl;

            while (progressTime < deltaTime) {
                deltaTime -= progressTime;
                t.current_time += progressTime;
                if (t.repeat && t.current_time > t.baseTime)
                    t.current_time -= t.baseTime;
                
                if (t.nextEvent->callback)
                    t.nextEvent->callback(t.current_time, 0);

                advanceIterators(t);
                if (t.nextEvent == t.events.end()) {
                    break;
                }

                progressTime = getProgressBeforeNextEvent(p.first);
            }

            t.current_time += deltaTime;
        }
    }
}

void Animate::createAnimation(std::string const& name) {
    timelines[name] = {};
}

void Animate::createEvent(std::string const& anim_name, float time, Callback const& callback) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        Animate::Event e = { callback, time };
        anim->second.events.insert( e );

        setEventIteratorsOf(anim->second);
    } else {
        assert(false);
    }
}

float Animate::getAnimationTime(std::string const& anim_name) const {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        return anim->second.current_time;
    } else {
        assert(false);
    }
}

float Animate::getProgress(std::string const& anim_name) const {
    auto anim = timelines.find(anim_name);
    if (anim != timelines.end()) {
        assert(anim->second.nextEvent != anim->second.events.end());
        float diffMax = 0;
        float diff = 0;
        if (differenceForward(anim->second, anim->second.prevEvent->time, anim->second.nextEvent->time, diffMax)) {
            if (differenceForward(anim->second, anim->second.current_time, anim->second.nextEvent->time, diff)) {
                assert(diffMax != 0);
                return diff / diffMax;
            }
        }
    }
    assert(false);
}

float Animate::getProgressBeforeNextEvent(std::string const& anim_name) const {
    auto anim = timelines.find(anim_name);
    if (anim != timelines.end()) {
        assert(anim->second.nextEvent != anim->second.events.end());
        float diff = 0;
        if (differenceForward(anim->second, anim->second.current_time, anim->second.nextEvent->time, diff)) {
            return diff;
        }
    }
    assert(false);
}

void Animate::setRepeated(std::string const& anim_name, bool repeating, float baseTime) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        anim->second.repeat = repeating;
        anim->second.baseTime = baseTime;  

        setEventIteratorsOf(anim->second);
    } else {
        assert(false);
    }
}

void Animate::setEventIteratorsOf(Timeline& t) {
    t.nextEvent = t.events.end();
    t.prevEvent = t.events.end();
    float minTime_next = 0;
    float minTime_prev = 0;
    float cur_time = t.current_time;

    int i = 0;
    for (auto it = t.events.begin(); it != t.events.end(); ++it) {
        Event const& e = *it;
        float timeDiff;
        if (differenceForward(t, cur_time, e.time, timeDiff)) {
            if (timeDiff < minTime_next || t.nextEvent == t.events.end()) {
                t.nextEvent = it;
            }
        }
        if (differenceBackward(t, cur_time, e.time, timeDiff)) {
            if (timeDiff <= minTime_prev || t.prevEvent == t.events.end()) {
                t.prevEvent = it;
            }
        }
        i++;
    }
}

void Animate::advanceIterators (Timeline& t) {
    t.prevEvent = t.nextEvent;
    t.nextEvent++;
    if (t.nextEvent == t.events.end()) {
        if (t.repeat && t.events.size() > 0)
            t.nextEvent = t.events.begin();
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
    if (time0 > time1) {
        result = time0 - time1;
        return true;
    }
    if (t.repeat) {
        result = time0 + t.baseTime - time1;
        return true;
    }

    return false;
}
