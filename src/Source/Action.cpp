#include "../Header/Action.h"

Action::Action() {

}

Action::~Action() {

}

BasicAttack::BasicAttack(Type type, Area area, int min_dist, int max_dist) : Action(), type(type), area(area), min_distance(min_dist), max_distance(max_dist) {
    
}

BasicAttack::BasicAttack() {
    
}

BasicAttack::~BasicAttack() {

}

std::vector<const Hex*> BasicAttack::getPossibleCells(Map const& map, const Hex* caster_cell) {
    auto hexes = map.filterHexs([&] (const Hex* hex) {
        auto d = map.hexDistance(caster_cell, hex);
        return d > min_distance && d <= max_distance && (type != Type::INLINE || caster_cell->isOnSameLine(hex));
    });
    return std::move(hexes);
}