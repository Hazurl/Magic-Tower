#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include <Utilities/Constant.h>
#include <Utilities/DebugMacro.h>
#include <Utilities/RessourcesLoader.h>
#include <Utilities/SceneManager.h>
#include <Utilities/Input.h>

#include <GameState/Camera.h>

#include <Components/Renderer/HexRenderer.h>

#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/GameObject/Environement.hpp>
#include <frameworkHaz/GameObject/2D/Physic.hpp>
#include <frameworkHaz/Tools/Time.hpp>

class GameEngine {
    GIVE_ACCESS_DEBUG()
public:
    GameEngine();
    ~GameEngine();

    int start();

private:
    void manageEvents();
    void manageUpdates(haz::Time const& time);
    void manageDraw();

    sf::RenderWindow window;

    haz::Environement env;
};

#endif