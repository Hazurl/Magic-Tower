#include <GameState/Unit.h>

Unit::Unit(const Hex* hex) : hex(hex) {
    actions.emplace_back(new BasicAttack());
}

Unit::~Unit() {
    for (auto* action : actions)
        delete action;
}

const Hex* Unit::getHex() const {
    return hex;
}

std::vector<const Hex*> Unit::getPossibleActionHexes(Map const& map, unsigned int action) const {
    if (action >= actions.size())
        return {};

    return actions[action]->getPossibleHexes(map, hex);
}