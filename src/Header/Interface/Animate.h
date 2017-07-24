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
    typedef std::function<void(float /*current time*/, float /*time before next*/, float /*time between previous and next*/)> Callback;

    Animate();
    virtual ~Animate();

    void createAnimation(std::string const& name);
    void createEvent(std::string const& anim_name, float time, Callback const& callback = nullptr);

    float getAnimationTime(std::string const& anim_name) const;
    float getProgress(std::string const& anim_name) const;
    float getTimeBeforeNextEvent(std::string const& anim_name) const;

    void setRepeated(std::string const& anim_name, bool repeat, float baseTime = 1000);
    void setSpeed(std::string const& anim_name, float speed);

private:
    struct EventList {
        EventList (Callback const& callback, float time) : callback(callback), time(time) { assert(time >= 0); }
        Callback callback = nullptr;
        float time = 0;

        EventList* prev = nullptr;
        EventList* next = nullptr;

        bool is_first = false;
        bool is_last = false;
    };

    struct Timeline {
        ~Timeline();

        EventList* first;
        EventList* current;
        EventList* next;

        float repeat = false;
        float baseTime = 1000;  // ms
        float current_time = 0; // ms
        float speed = 1;
    };

    std::map<std::string, Timeline> timelines = {};

    void advanceTimelinePtrs(Timeline& t);

    bool differenceForward(Timeline const& t, float time0, float time1, float& result) const;
    bool differenceBackward(Timeline const& t, float time0, float time1, float& result) const;

    float getProgress(Timeline const& t) const;
    float getTimeBeforeNextEvent(Timeline const& t) const;

    Timeline& getTimeline(std::string const& anim_name);
    Timeline const& getTimeline(std::string const& anim_name) const;

    void recalculatePointers(Timeline& t);

    void insertEvent(Timeline& t, Callback const& callback, float time);
};

#endif