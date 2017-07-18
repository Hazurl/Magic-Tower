#include "../Header/GameEngine.h"

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower"), map(10), player(nullptr) {

}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
    Unit unit;

    for (const auto* h : unit.actions[0]->getPossibleCells(map, map.getHexAt(0,3)))
        map.highlightHex(h);

#if DEBUG > 0
    Debug debug(&map, &player);
#endif
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            manageEvent(event);
        }

#if DEBUG > 0
        debug.update();
#endif

        window.clear(sf::Color::White);

        map.draw(window);

        window.display();
    }

    RessourcesLoader::clearAll();

    return 0;
}

void GameEngine::manageEvent (sf::Event const& e) {
    switch (e.type) {
    case sf::Event::Closed:
        window.close();
    break;

    default: break;
    }
}
