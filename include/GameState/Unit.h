#ifndef __UNIT
#define __UNIT

#include <SFML/Graphics.hpp>
#include <vector>

#include <Action/Action.h>
#include <Utilities/DebugMacro.h>

class Unit {
    GIVE_ACCESS_DEBUG()
public:
    Unit(const Hex* hex);
    virtual ~Unit();

    const Hex* getHex() const;

private:
    int movement_point = 1;
    std::vector<Action*> actions = {};

    const Hex* hex;
};

#endif 