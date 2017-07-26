#ifndef __TRIGGERS
#define __TRIGGERS

#include <iostream>

namespace Triggers {
class Event {
public:
    Event();
    virtual ~Event();

    // 0 means nothing, 1 or more means the event is active
    virtual float getProgress(float deltaTime) = 0;
    virtual Event* clone() = 0;
    virtual void reset();
};

class EventElapsedTimePassed : public Event {
public:
    EventElapsedTimePassed(float time);
    virtual ~EventElapsedTimePassed();
    virtual float getProgress(float deltaTime);
    virtual void reset();
    virtual Event* clone();

protected:
    const float time = 0;
    float cur_time = 0;
};

class EventCallback : public Event {
public:
    typedef float(*Callback)(float); // function (float) -> float

    EventCallback(Callback const& callback);
    virtual ~EventCallback();
    virtual float getProgress(float deltaTime);
    virtual Event* clone();

protected:
    const Callback callback = nullptr;
};

class EventBinaryEvent : public Event {
public:
    EventBinaryEvent(Event* e_left, Event* e_right);
    virtual ~EventBinaryEvent();
    virtual void reset();

protected:
    Event* e_left = nullptr;
    Event* e_right = nullptr;
};

class EventOr : public EventBinaryEvent {
public:
    EventOr(Event* e_left, Event* e_right);
    virtual ~EventOr();
    virtual float getProgress(float deltaTime);
    virtual Event* clone();
};

class EventAnd : public EventBinaryEvent {
public:
    EventAnd(Event* e_left, Event* e_right);
    virtual ~EventAnd();
    virtual float getProgress(float deltaTime);
    virtual Event* clone();
};

} //namespace Triggers

#endif