#include <Utilities/GameEngine.h>

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
    SceneManager::changeScene(SceneManager::Scene::Game);

    haz::Time time;

    env.addGameObject(new haz::GameObject("hex_0_0"))->addComponent<HexRenderer>();

    while (window.isOpen()) {
        time.update();

        SceneManager::onNewFrame();

        manageEvents();
        manageUpdates(time);
        manageDraw();
    }

    return 0;
}

void GameEngine::manageEvents() {
    Input::resetEvents();
    sf::Event e;
    while (window.pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseWheelScrolled:
            Input::onScrollEvent(e.mouseWheelScroll.delta);
            break;

        default: 
            break;
        }
    }
}

void GameEngine::manageDraw() {
    window.clear(sf::Color(50, 50, 50));

    auto hexesRend = Renderer::getRenderers();

    if (hexesRend.size())
        hexesRend[0]->draw(window, {0, 0, 1});
    else
        std::cout << "No hex !" << std::endl;

    window.display();
}

void GameEngine::manageUpdates(haz::Time const& time) {
    Input::updateButtonsStates(window);

    auto hexes_raycast = haz::_2D::Physic::raycast_all(&env, Input::getMousePosition(), haz::Layers::Ground);
}
