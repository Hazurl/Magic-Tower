#ifndef __PLAYER
#define __PLAYER

#include "DebugMacro.h"
#include "Hex.h"

class Player {
    GIVE_ACCESS_DEBUG()

public:
    Player(const Hex* hex);
    ~Player();

private:
    const Hex* hex;
};

#endif