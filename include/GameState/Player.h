#ifndef __PLAYER
#define __PLAYER

#include <GameState/Hex.h>
#include <GameState/Unit.h>

class Player : public Unit {
    GIVE_ACCESS_DEBUG()

public:
    Player(const Hex* hex);
    ~Player();

    int getMP() const;

private:
    int movePoints;
};

#endif