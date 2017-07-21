#ifndef __GAMEOBJECT
#define __GAMEOBJECT

#include "../Utilities/Input.h"

class GameObject {
public:

    GameObject();
    virtual ~GameObject();

    virtual void update(Input const& inputs) = 0;

private:

};

#endif