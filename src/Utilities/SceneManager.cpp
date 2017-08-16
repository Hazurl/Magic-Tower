#include <Utilities/SceneManager.h>

SceneManager::Scene SceneManager::current = SCENE_MANAGER_DEFAULT_SCENE;
SceneManager::Scene SceneManager::next = SCENE_MANAGER_DEFAULT_SCENE;

SceneManager::Scene SceneManager::getCurrentScene() {
    return SceneManager::current;
}

int SceneManager::getCurrentIDScene() {
    return static_cast<int>(SceneManager::current);
}

void SceneManager::changeScene(SceneManager::Scene const& id) {
    SceneManager::next = id;
}

void SceneManager::onNewFrame() {
    if (SceneManager::current != SceneManager::next) {
        FontLoader::releaseScene(SceneManager::getCurrentIDScene());
        TextureLoader::releaseScene(SceneManager::getCurrentIDScene());

        SceneManager::current = SceneManager::next;
        SceneManager::onSceneLoad(SceneManager::current);
    }
}

void SceneManager::onSceneLoad(SceneManager::Scene const& scene) {
    int sceneId = static_cast<int>(scene);
    switch(scene) {
        case SceneManager::Scene::Game:
            TextureLoader::load(sceneId, "image/Ground.png", "hex_ground");
            TextureLoader::load(sceneId, "image/wall.png", "hex_wall");
            TextureLoader::load(sceneId, "image/lava.png", "hex_lava");
            TextureLoader::load(sceneId, "image/hat.png", "unit_player");
            TextureLoader::load(sceneId, "image/warrior.png", "unit_enemy");
        
            FontLoader::load(sceneId, "Font/Roboto-Regular.ttf", "roboto");
        break;

        case SceneManager::Scene::Menu:
        
        break;

        default:
            break;
    }
}