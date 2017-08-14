#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include <Utilities/Constant.h>
#include <Utilities/DebugMacro.h>
#include <Utilities/RessourcesLoader.h>
#include <Utilities/Input.h>
#include <Utilities/GameRenderer.h>

#include <GameState/GameState.h>

#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/GameObject/Environement.hpp>
#include <frameworkHaz/GameObject/2D/Physic.hpp>

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

    haz::Environement env;
};

#endif