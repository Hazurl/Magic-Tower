/*#include <GameState/Player.h>

Player::Player(const Hex* hex) : Unit(hex), movePoints(3) {
    actions.emplace_back(new BasicAttack(BasicAttack::Type::BASIC, BasicAttack::Area::POINT, 0, 1));
    actions.emplace_back(new BasicAttack(BasicAttack::Type::INLINE, BasicAttack::Area::CIRCLE_1, 0, 4));
    actions.emplace_back(new BasicAttack(BasicAttack::Type::BASIC, BasicAttack::Area::POINT, 3, 7));
}

Player::~Player() {

}

int Player::getMP() const {
    return movePoints;
}*/