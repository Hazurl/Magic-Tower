#ifndef __ACTION
#define __ACTION

#include "Map.h"
#include <iostream>

class Action {
public:
    Action();
    virtual ~Action();

    virtual std::vector<const Hex*> getPossibleCells(Map const& map, const Hex* caster_cell) = 0;

private:
    int cooldown = 0;
};

class BasicAttack : public Action {
public:
    enum class Type {
        INLINE, BASIC
    };

    enum class Area {
        LASER, POINT, CONE, CIRCLE_1, CIRCLE_2
    };

    BasicAttack(Type type, Area area, int min_dist, int max_dist);
    BasicAttack();
    virtual ~BasicAttack();

    std::vector<const Hex*> getPossibleCells(Map const& map, const Hex* caster_cell);

private:
    Type type = Type::INLINE;
    Area area = Area::POINT;

    int min_distance = 0;
    int max_distance = 1;
};

#endif