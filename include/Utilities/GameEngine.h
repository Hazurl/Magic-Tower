#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include <Utilities/Constant.h>
#include <Utilities/DebugMacro.h>
#include <Utilities/Debug.h>
#include <Utilities/RessourcesLoader.h>
#include <Utilities/Input.h>
#include <Utilities/GameRenderer.h>

#include <GameState/GameState.h>

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