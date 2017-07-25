#ifndef __Animation
#define __Animation

#include <map>
#include <list>
#include <initializer_list>

namespace Triggers {
class Event {
public:
    Event();
    virtual ~Event();

    // 0 means nothing, 1 or more means the event is active
    virtual float getProgress(float deltaTime) = 0;
    virtual void reset();
};

class EventElapsedTimePassed : public Event {
public:
    EventElapsedTimePassed(float time);
    virtual ~EventElapsedTimePassed();
    virtual float getProgress(float deltaTime);
    virtual void reset();

protected:
    const float time;
    float cur_time;
};

class EventCallback : public Event {
public:
    typedef float(*Callback)(float); // function (float) -> float

    EventCallback(Callback const& callback);
    virtual ~EventCallback();
    virtual float getProgress(float deltaTime);

protected:
    const Callback callback;
};

class EventBinaryEvent : public Event {
public:
    EventBinaryEvent(Event* e_left, Event* e_right);
    virtual ~EventBinaryEvent();
    virtual void reset();

protected:
    Event* e_left;
    Event* e_right;
};

class EventOr : public EventBinaryEvent {
public:
    EventOr(Event* e_left, Event* e_right);
    virtual ~EventOr();
    virtual float getProgress(float deltaTime);
};

class EventAnd : public EventBinaryEvent {
public:
    EventAnd(Event* e_left, Event* e_right);
    virtual ~EventAnd();
    virtual float getProgress(float deltaTime);
};
} //namespace Triggers

class Animator {
protected:
    Animator();
    virtual ~Animator();
    virtual void updateAnimations(float deltaTime) = 0;
};

template<typename TState>
class Animation {
private:
    struct Transition {
        Transition(TState const& next_state, Triggers::Event* trigger);
        ~Transition();

        const TState next_state;
        Triggers::Event* trigger;
    };

    struct StateInfo {
        StateInfo();
        ~StateInfo();

        float checkTransitions(float deltaTime, TState& result);
        void reset();

        std::list<Transition> transitions = {};
    };

public:
    Animation(TState const& currentState);
    virtual ~Animation();

    void addState(TState const& state);
    void removeState(TState const& state);
    
    void addTransitionsFrom(TState const& state, std::initializer_list<std::pair<TState, Triggers::Event*>> const& transitions);
    void removeTransitionsBetween(TState const& from, TState const& to);

    void setState (TState const& state); 
    TState getCurrentState () const;
    float getProgress() const;

    void update (float deltaTime);
    
private:
    std::map<TState, StateInfo> statesInfos = {};

    TState currentState;
    float progress = 0;
};

#endif