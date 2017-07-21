#include "../../Header/Interface/Animate.h"

Animate::Animate() {

}

Animate::~Animate() {

}

void Animate::update(float deltaTime) {
    for (auto& p : timelines) {
        Timeline& t = p.second;
        float previous_time = t.current_time;
        float current_time = previous_time + deltaTime;
        float time_repeated = current_time;
        if (t.repeat)
            time_repeated -= static_cast<int>(time_repeated / t.baseTime) * t.baseTime;

        // TODO : multiple event call in one update
        for (auto e : t.events) {
            if (e.time > previous_time && e.time <= current_time && (!t.repeat || t.baseTime > e.time))
                e.callback(time_repeated, 0); // TODO : getNextEventTime
        }

        t.current_time = time_repeated;
    }
}

void Animate::createAnimation(std::string const& name) {
    timelines[name] = {};
}

void Animate::createEvent(std::string const& anim_name, float time, Callback const& callback) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        Animate::Event e { callback, time };
        anim->second.events.emplace_back( e );
    } else {
        assert(false);
    }
}

float Animate::getAnimationTime(std::string const& anim_name) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        return anim->second.current_time;
    } else {
        assert(false);
    }
}

void Animate::setRepeated(std::string const& anim_name, bool repeating, float baseTime) {
    auto anim = timelines.find(anim_name) ;
    if (anim != timelines.end()) {
        anim->second.repeat = repeating;
        anim->second.baseTime = baseTime;        
    } else {
        assert(false);
    }
}
