#ifndef __HAZ_SCENEMANAGER
#define __HAZ_SCENEMANAGER

#include <string>
#include <Utilities/RessourcesLoader.h>

#define SCENE_MANAGER_DEFAULT_SCENE SceneManager::Scene::Unknown

class SceneManager {
public:
    enum class Scene {
        Menu, Game,

        Unknown
    };

    static Scene getCurrentScene();
    static void changeScene(Scene const& id);

    static void onNewFrame();
    static void onSceneLoad(Scene const& scene);

private:

    static Scene current;
    static Scene next;

};

#endif
