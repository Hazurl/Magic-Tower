/*#include <GameState/Unit.h>

Unit::Unit(const Hex* hex) : hex(hex) {
    
}

Unit::~Unit() {
    for (auto* action : actions)
        delete action;
}

const Hex* Unit::getHex() const {
    return hex;
}

void Unit::setHex(const Hex* h) {
    hex = h;
}

std::vector<const Hex*> Unit::getPossibleActionHexes(Map const& map, unsigned int action) const {
    if (action >= actions.size())
        return {};

    return actions[action]->getPossibleHexes(map, hex);
}

void Unit::doAction (Map const& map, unsigned int action, const Hex* hex) {
    if (action < actions.size())
        return actions[action]->execute(map, hex);
}*/