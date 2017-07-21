#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define WINDOW_FPS 5

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include "DebugMacro.h"
#include "Debug.h"
#include "RessourcesLoader.h"
#include "Input.h"

#include "Map.h"
#include "Player.h"
#include "Unit.h"

class GameEngine {
    GIVE_ACCESS_DEBUG()

public:
    GameEngine();
    ~GameEngine();

    int start();

private:
    void manageEvents();
    void manageUpdates();
    void manageDraw();

    sf::RenderWindow window;

    Map map;
    Player player;
    Input inputs;
#if DEBUG > 0
    Debug debug;
#endif
};

#endif