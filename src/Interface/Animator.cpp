#include <Interface/Animator.h>

/*      Animator CLASS
 *
 *  Interface
 */

Animator::Animator() { }
Animator::~Animator() { }

/*      Animation CLASS
 *
 *  Responsible to contains all State
 */

template<typename TState>
Animation<TState>::Animation(TState const& state) {
    addState(state);
    setState(state);
}

template<typename TState>
Animation<TState>::~Animation() { }

template<typename TState>
void Animation<TState>::addState(TState const& state) {
    assert(statesInfos.find(state) == statesInfos.end());
    statesInfos.insert(state, StateInfo());
}

template<typename TState>
void Animation<TState>::removeState(TState const& state) {
    assert(state != currentState);
    assert(statesInfos.find(state) != statesInfos.end());

    StateInfo& info = statesInfos[state];
    for (auto& state_info : statesInfos) {
        if (state_info.first == state)
            continue;

        for (auto it = state_info.second.transitions.begin(); it != state_info.second.transitions.end();) {
            if (it->next_state == state) {
                auto to_remove = it;
                ++it;
                state_info.second.erase(to_remove);
            } else {
                ++it;
            }
        }
    }

    statesInfos.erase(state);
}

template<typename TState>
void Animation<TState>::addTransitionsFrom(TState const& state, std::initializer_list<std::pair<TState, Triggers::Event*>> const& transitions) {
    assert(statesInfos.find(state) != statesInfos.end());

    StateInfo& info = statesInfos[state];

    for (auto& pair : transitions) {
        info.transitions.push_back(Transition(pair.first, pair.second));
    }
}

template<typename TState>
void Animation<TState>::removeTransitionsBetween(TState const& from, TState const& to) {
    assert(statesInfos.find(from) != statesInfos.end());

    StateInfo& info = statesInfos[from];

    for (auto it = info.transitions.begin(); it != info.transitions.end();) {
        if (it->next_state == to) {
            auto to_remove = it;
            ++it;
            info.erase(to_remove);
        } else {
            ++it;
        }
    }
}

template<typename TState>
void Animation<TState>::setState (TState const& state) {
    assert(statesInfos.find(state) != statesInfos.end());

    currentState = state;
    statesInfos[state].reset();
}

template<typename TState>
TState Animation<TState>::getCurrentState () const {
    return currentState;
}

template<typename TState>
void Animation<TState>::update (float deltaTime) {
    assert(statesInfos.find(currentState) != statesInfos.end());

    progress = statesInfos[currentState].checkTransitions(deltaTime, currentState);

    assert(statesInfos.find(currentState) != statesInfos.end());
}

template<typename TState>
float Animation<TState>::getProgress () const {
    return progress;
}

/*      StateInfo CLASS
 *
 *  Contains Transition to other States
 */

template<typename TState>
Animation<TState>::StateInfo::StateInfo () { }

template<typename TState>
Animation<TState>::StateInfo::~StateInfo () { }

template<typename TState>
float Animation<TState>::StateInfo::checkTransitions(float deltaTime, TState& result) {
    float max = 0;
    for (auto& t : transitions) {
        if (t.trigger != nullptr) { // event = null means TRUE
            float progress = t.trigger->getProgress(deltaTime);
            if (progress >= 1) {
                result = t.next_state;
                return 1;
            }
            if (max < progress)
                max = progress;
        } else {
            result = t.next_state;
            return 1;
        }
    }

    return max;
}

template<typename TState>
void Animation<TState>::StateInfo::reset() {
    for (auto& t : transitions)
        if (t.trigger != nullptr)
            t.trigger->reset();
}

/*      Transition CLASS
 *
 *  Contains an event and the next_state
 */

template<typename TState>
Animation<TState>::Transition::Transition(TState const& next_state, Triggers::Event* trigger) : next_state(next_state), trigger(trigger) { }

template<typename TState>
Animation<TState>::Transition::~Transition() {
    if (trigger)
        delete trigger;
}

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

EventAnd::~EventAnd() { }

float EventAnd::getProgress(float deltaTime) {
    float progress_left = (e_left == nullptr ? 1 : e_left->getProgress(deltaTime));
    float progress_right = (e_right == nullptr ? 1 : e_right->getProgress(deltaTime));

    return progress_left < progress_right ?
            progress_left
        :   progress_right;
}

} //namespace Triggers