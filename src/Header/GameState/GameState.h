#ifndef __GAMESTATE
#define __GAMESTATE

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "../Utilities/DebugMacro.h"

class GameState {
    GIVE_ACCESS_DEBUG()
    
public:
    GameState();
    ~GameState();

private:
    Map map;
    Player* player;
    std::vector<Enemy*> enemies = {};
};

#endif