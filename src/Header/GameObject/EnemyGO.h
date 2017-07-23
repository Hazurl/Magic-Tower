#ifndef __ENEMYGO
#define __ENEMYGO

#include "../Interface/Animate.h"
#include "../GameState/Enemy.h"

class EnemyGO : public Animate, public Enemy {
public:
    EnemyGO(const Hex* hex);
    ~EnemyGO();

private:

};

#endif