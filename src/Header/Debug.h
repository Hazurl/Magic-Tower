#ifndef __DEBUG
#define __DEBUG

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <typeinfo>
#include <iostream>

#include "RessourcesLoader.h"
#include "DebugMacro.h"
#include "Map.h"
#include "Hex.h"
#include "UI.h"

class Debug {
public:
    Debug();
    ~Debug();

    void use (const Map* map);
    void update();

private:
    UI::Panel* load (const Map* map);
    UI::Panel* load (const Hex* map);

    sf::Text createText(sf::String const& str);
    UI::Panel* createCollapsablePanel(std::string const& name, sf::Text title, std::function<void(UI::Panel*)> onClickFunc);

    const Map* map;

    sf::RenderWindow window;
    UI ui;
};

#endif