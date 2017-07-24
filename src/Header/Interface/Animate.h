#ifndef __ANIMATE
#define __ANIMATE

#include <map>
#include <set>
#include <cassert>
#include <string>
#include <functional>
#include <iostream>

class Animate {
public:
    void update(float deltaTime);

protected:
    typedef std::function<void(float /*time*/, float /*next_event*/)> Callback;
    Animate();
    virtual ~Animate();

    void createAnimation(std::string const& name);
    void createEvent(std::string const& anim_name, float time, Callback const& callback = nullptr);

    float getAnimationTime(std::string const& anim_name) const;
    float getProgress(std::string const& anim_name) const;
    float getProgressBeforeNextEvent(std::string const& anim_name) const;
    void setRepeated(std::string const& anim_name, bool repeating, float baseTime = 1000);

private:
    struct Event {
        Callback callback = nullptr;
        float time = 0;
    };

    struct EventCompare {
        bool operator() (Event const& le, Event const& re) const {
            return le.time < re.time;
        }
    };

    struct Timeline {
        std::multiset<Event, EventCompare> events = {};
        typedef decltype(events)::iterator EventIterator;

        float repeat = false;
        float baseTime = 1000;  // ms
        float current_time = 0; // ms
        EventIterator nextEvent = events.end();
        EventIterator prevEvent = events.end();
    };

    std::map<std::string, Timeline> timelines = {};

    void setEventIteratorsOf(Timeline& t);
    void advanceIterators(Timeline& t);

    bool differenceForward(Timeline const& t, float time0, float time1, float& result) const;
    bool differenceBackward(Timeline const& t, float time0, float time1, float& result) const;

};

#endif