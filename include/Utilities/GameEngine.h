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
#include <Utilities/PrefabFactory.h>
#include <Utilities/Converter.h>

#include <Components/Camera/Camera.h>
#include <Components/Camera/CameraMotionControler.h>

#include <Components/Renderer/Renderer.h>
#include <Components/Data/Hex.h>
#include <Components/Data/Map.h>

#include <frameworkHaz/2DGOInclude.hpp>

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

    Camera* camera;
};

#endif