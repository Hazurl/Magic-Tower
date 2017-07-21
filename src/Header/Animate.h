#ifndef __ANIMATE
#define __ANIMATE

#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <functional>
#include <iostream>

class Animate {
public:
    typedef std::function<void(float /*time*/, float /*next_event*/)> Callback;
    Animate();
    ~Animate();

    void update(float deltaTime);

    void createAnimation(std::string const& name);
    void createEvent(std::string const& anim_name, float time, Callback const& callback);

    float getAnimationTime(std::string const& anim_name);
    void setRepeated(std::string const& anim_name, bool repeating, float baseTime = 1000);

private:
    struct Event {
        Callback callback = nullptr;
        float time = 0;
    };
    struct Timeline {
        std::vector<Event> events = {};
        float repeat = false;
        float baseTime = 1000;  // ms
        float current_time = 0; // ms
    };

    std::map<std::string, Timeline> timelines = {};
};

#endif