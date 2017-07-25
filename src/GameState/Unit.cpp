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