#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include "DebugMacro.h"
#include "Debug.h"
#include "RessourcesLoader.h"

#include "Map.h"
#include "Player.h"
#include "Unit.h"

class GameEngine {
    GIVE_ACCESS_DEBUG()

public:
    GameEngine();
    ~GameEngine();

    int start();

    void manageEvent (sf::Event const& e);

private:
    sf::RenderWindow window;

    Map map;
    Player player;
};

#endif