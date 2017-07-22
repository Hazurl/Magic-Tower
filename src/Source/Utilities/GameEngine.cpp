#include "../../Header/Utilities/GameEngine.h"

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close), {
    window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
#if DEBUG > 0
    debug.use(&map);
    debug.use(&player);
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
    sf::Event e;
    while (window.pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            window.close();
            break;

        default: 
            break;
        }
    }
}

void GameEngine::manageDraw() {
    window.clear(sf::Color::White);

    //map.draw(window);

    window.display();
}

void GameEngine::manageUpdates(float /*deltaTime*/) {
#if DEBUG > 0
    debug.update();
#endif
    inputs.updateButtonsStates();
}
