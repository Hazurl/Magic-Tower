#include "../../Header/Utilities/GameEngine.h"

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
#if DEBUG > 0
    debug.use(&gameState);
    debug.use(&inputs);
#endif

    sf::Clock clock;

    while (window.isOpen()) {
        manageEvents();
        manageUpdates(clock.restart().asMilliseconds());
        manageDraw();
    }

    RessourcesLoader::clearAll();

    return 0;
}

void GameEngine::manageEvents() {
    inputs.resetEvents();
    sf::Event e;
    while (window.pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseWheelScrolled:
            inputs.onScrollEvent(e.mouseWheelScroll.delta);
            break;

        default: 
            break;
        }
    }
}

void GameEngine::manageDraw() {
    window.clear(sf::Color(50, 50, 50));

    gameRenderer.render(window, gameState);

    window.display();
}

void GameEngine::manageUpdates(float deltaTime) {
#if DEBUG > 0
    debug.update();
#endif
    inputs.updateButtonsStates(window);

    auto hexes_raycast = gameRenderer.raycast_hexLayer(inputs.getMouseX(), inputs.getMouseY());
    
#if DEBUG > 1
    if (inputs.isDown(Input::Button::Space)) {
        for (auto* hex : hexes_raycast) {
            std::cout << "Hex (" << hex->getX() << ", " << hex->getY() << ")" << std::endl;
        }
    }
#endif

    gameState.updateInputs(inputs, hexes_raycast);
    gameState.updateAnimations(deltaTime);
}
