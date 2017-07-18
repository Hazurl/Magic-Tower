#ifndef __UNIT
#define __UNIT

#include <SFML/Graphics.hpp>
#include <vector>
#include "Action.h"

class Unit {
public:
    Unit();
    ~Unit();
    std::vector<Action*> actions = {};

private:
    int movement_point = 1;
};

#endif 