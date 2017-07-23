#ifndef __PLAYER
#define __PLAYER

#include "Hex.h"
#include "Unit.h"

class Player : public Unit {
    GIVE_ACCESS_DEBUG()

public:
    Player(const Hex* hex);
    ~Player();

private:

};

#endif