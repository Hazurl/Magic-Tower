#include "../../Header/GameState/Unit.h"

Unit::Unit() {
    actions.emplace_back(new BasicAttack());
}

Unit::~Unit() {
    for (auto* action : actions)
        delete action;
}

