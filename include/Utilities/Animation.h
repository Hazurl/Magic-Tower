#ifndef __ANIMATION
#define __ANIMATION

#include <map>
#include <list>
#include <initializer_list>
#include <vector>

#include <Utilities/Triggers.h>

template<typename TState>
class Animation {
private:
    struct Transition {
        Transition(TState const& next_state, Triggers::Event* trigger) : next_state(next_state), trigger(trigger) {
        }

        ~Transition() {
            if (trigger)
                delete trigger;
        }

        Transition(Transition const& other) : next_state(other.next_state), trigger(other.trigger == nullptr ? nullptr : other.trigger->clone()) {
        }

        const TState next_state;
        Triggers::Event* trigger = nullptr;
    };

    struct StateInfo {
        StateInfo() {}
        ~StateInfo() {}

        bool checkTransitions(float deltaTime, TState& result, float& progress) {
            float max = 0;
            for (auto& t : transitions) {
                if (t.trigger != nullptr) { // event = null means TRUE
                    float progress = t.trigger->getProgress(deltaTime);
                    if (progress >= 1) {
                        result = t.next_state;
                        progress = 1;
                        return true;
                    }
                    if (max < progress)
                        max = progress;
                } else {
                    result = t.next_state;
                    progress = 1;
                    return true;
                }
            }

            progress = max;
            return false;
        }
        void reset() {
            for (auto& t : transitions)
                if (t.trigger != nullptr)
                    t.trigger->reset();
        }
        std::list<Transition> transitions = {};
    };

public:
    typedef void(*Callback)(TState const&);

    Animation(TState const& state) {
        addState(state);
        setState(state);
    }
    ~Animation() { }

    void onStateChange(Callback const& callback) {
        onStateChangeCallback.push_back(callback);
    }

    void cleanOnStateChange() {
        onStateChangeCallback.clean();
    }

    void addState(TState const& state) {
        assert(statesInfos.find(state) == statesInfos.end());
        statesInfos.emplace(state, StateInfo());
    }
    void removeState(TState const& state) {
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
    void addTransitionsFrom(TState const& state, std::initializer_list<std::pair<TState, Triggers::Event*>>const& transitions) {
        assert(statesInfos.find(state) != statesInfos.end());

        StateInfo& info = statesInfos[state];

        for (auto& pair : transitions) {
            info.transitions.emplace_back(pair.first, pair.second);
        }
    }
    void removeTransitionsBetween(TState const& from, TState const& to)  {
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
    void setState (TState const& state) {
        assert(statesInfos.find(state) != statesInfos.end());

        currentState = state;
        statesInfos[state].reset();
        for (auto& callback : onStateChangeCallback)
            if (callback)
                callback(currentState);
    }
    TState getState () const { return currentState; }
    float getProgress() const { return progress; }

    void update (float deltaTime) {
        assert(statesInfos.find(currentState) != statesInfos.end());

        auto& info = statesInfos[currentState];
        if (info.checkTransitions(deltaTime, currentState, progress)) {
            info.reset();
            for (auto& callback : onStateChangeCallback)
                if (callback)
                    callback(currentState);
        }

        assert(statesInfos.find(currentState) != statesInfos.end());
    }

private:
    std::map<TState, StateInfo> statesInfos = {};
    std::vector<Callback> onStateChangeCallback = {};

    TState currentState;
    float progress = 0;
};

#endif