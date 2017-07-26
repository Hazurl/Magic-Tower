#ifndef __ANIMATOR
#define __ANIMATOR

#include <Utilities/Animation.h>

class Animator {
protected:
    Animator();
    virtual ~Animator();
    virtual void updateAnimations(float deltaTime) = 0;
};

#endif