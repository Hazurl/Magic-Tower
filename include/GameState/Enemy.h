#ifndef __ENEMY
#define __ENEMY

#include <GameState/Unit.h>
#include <Action/Action.h>

class Enemy : public Unit {
public:
    Enemy(const Hex* hex);
    virtual ~Enemy();

private:

};

#endif