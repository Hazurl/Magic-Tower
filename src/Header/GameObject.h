#ifndef __GAMEOBJECT
#define __GAMEOBJECT

#include "Input.h"

class GameObject {
public:

    GameObject();
    virtual ~GameObject();

    virtual void update(Input const& inputs) = 0;

private:

};

#endif