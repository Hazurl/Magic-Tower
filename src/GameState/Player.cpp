#include <GameState/Player.h>

Player::Player(const Hex* hex) : Unit(hex), movePoints(3) {

}

Player::~Player() {

}

int Player::getMP() const {
    return movePoints;
}