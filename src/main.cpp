#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>


#include "Header/Map.h"
#include "Header/DebugMacro.h"
#include "Header/Debug.h"
#include "Header/Unit.h"
#include "Header/RessourcesLoader.h"

int main (int , char** ) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Magic Tower");
    Map map(10);
    //Unit unit;

    //unit.actions[0]->getPossibleCells(map, map.getHexAt(0,0));

#if DEBUG > 0
    Debug debug;
    debug.use(&map);
#endif
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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