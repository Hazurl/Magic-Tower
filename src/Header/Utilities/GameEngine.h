#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include "Constant.h"
#include "DebugMacro.h"
#include "Debug.h"
#include "RessourcesLoader.h"
#include "Input.h"
#include "GameRenderer.h"

#include "../GameState/GameState.h"

class GameEngine {
    GIVE_ACCESS_DEBUG()
public:
    GameEngine();
    ~GameEngine();

    int start();

private:
    void manageEvents();
    void manageUpdates(float deltaTime);
    void manageDraw();

    sf::RenderWindow window;

    GameState gameState;
    GameRenderer gameRenderer;
    
    Input inputs;
#if DEBUG > 0
    Debug debug;
#endif
};

#endif