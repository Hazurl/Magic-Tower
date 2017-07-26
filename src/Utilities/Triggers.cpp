#include <Utilities/Triggers.h>

namespace Triggers {
/*      Event CLASS
 *
 *  check something
 */

Event::Event() { }

Event::~Event() { }

void Event::reset() { }

/*
 *      Event ElapsedTimePassed
 */

EventElapsedTimePassed::EventElapsedTimePassed(float time) : Event(), time(time), cur_time(0) { }

EventElapsedTimePassed::~EventElapsedTimePassed() { }

Event* EventElapsedTimePassed::clone() {
    return new EventElapsedTimePassed(*this);
}

void EventElapsedTimePassed::reset() { 
    cur_time = 0;
}

float EventElapsedTimePassed::getProgress(float deltaTime) {
    if (time == 0)
        return 1;

    cur_time += deltaTime;
    return cur_time / time;
}

/*
 *      Event Callback
 */

EventCallback::EventCallback(Callback const& callback) : Event(), callback(callback) { }

EventCallback::~EventCallback() { }

Event* EventCallback::clone() {
    return new EventCallback(*this);
}

float EventCallback::getProgress(float deltaTime) {
    return callback == nullptr ? 1 : callback(deltaTime);
}

/*
 *      Event BinaryEvent
 */

EventBinaryEvent::EventBinaryEvent(Event* e_left, Event* e_right) : Event(), e_left(e_left), e_right(e_right) { }

EventBinaryEvent::~EventBinaryEvent() { 
    if (e_right)
        delete e_right;
    if (e_left)
        delete e_left;
}

void EventBinaryEvent::reset() { 
    if (e_left)
        e_left->reset();
    if (e_right)
        e_right->reset();
}

/*
 *      Event Or
 */

EventOr::EventOr(Event* e_left, Event* e_right) : EventBinaryEvent(e_left, e_right) { }

Event* EventOr::clone() {
    return new EventOr(*this);
}

EventOr::~EventOr() { }

float EventOr::getProgress(float deltaTime) {
    float progress_left = (e_left == nullptr ? 1 : e_left->getProgress(deltaTime));
    float progress_right = (e_right == nullptr ? 1 : e_right->getProgress(deltaTime));

    return progress_left > progress_right ?
            progress_left
        :   progress_right;
}

/*
 *      Event And
 */

EventAnd::EventAnd(Event* e_left, Event* e_right) : EventBinaryEvent(e_left, e_right) { }

Event* EventAnd::clone() {
    return new EventAnd(*this);
}

EventAnd::~EventAnd() { }

float EventAnd::getProgress(float deltaTime) {
    float progress_left = (e_left == nullptr ? 1 : e_left->getProgress(deltaTime));
    float progress_right = (e_right == nullptr ? 1 : e_right->getProgress(deltaTime));

    return progress_left < progress_right ?
            progress_left
        :   progress_right;
}

} //namespace Triggers
