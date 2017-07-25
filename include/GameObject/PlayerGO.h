#ifndef __PLAYERGO
#define __PLAYERGO

#include <Interface/Animate.h>
#include <GameState/Player.h>

class PlayerGO : public Animate, public Player {
public:
    PlayerGO(const Hex* hex);
    ~PlayerGO();

private:

};

#endif