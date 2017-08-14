#include <Utilities/GameEngine.h>

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
    sf::Clock clock;

    while (window.isOpen()) {
        manageEvents();
        manageUpdates(clock.restart().asMilliseconds());
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

    //gameRenderer.render(window, gameState);

    window.display();
}

void GameEngine::manageUpdates(float deltaTime) {
    Input::updateButtonsStates(window);

    auto hexes_raycast = haz::_2D::Physic::raycast_all(&env, Input::getMousePosition(), haz::Layers::Ground);
    
}
