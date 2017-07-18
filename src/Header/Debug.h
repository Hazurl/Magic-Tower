#ifndef __DEBUG
#define __DEBUG

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <map>

#include "RessourcesLoader.h"
#include "DebugMacro.h"
#include "Map.h"
#include "Hex.h"
#include "Player.h"
#include "UI.h"

#define DEBUG_ATTRIBUTE(attr) { std::string str = #attr; auto e = load(&attr, str.substr(str.find_last_of('>') + 1)); panel->push_back(e); }

#define DEBUG_CLASS(clazz, param, vars...)\
UI::Element* load(const clazz* param, std::string const& name) {\
    return createCollapsablePanel(#clazz, createText(#clazz " " + name), [param, this] (UI::Panel* panel) {\
        if (param) {\
            MAP(DEBUG_ATTRIBUTE, vars)\
        } else {\
            panel->push_back(new UI::Text(#param, createText("nullptr")));\
        }\
    });\
}

#define DEBUG_CONTAINER(clazz, param, func)\
UI::Element* load(const clazz* param, std::string const& name) {\
    return createCollapsablePanel(#clazz, createText(#clazz " " + name), [param, this] (UI::Panel* panel) {\
        if (param) {\
            for (auto& e : *param)\
                func(panel, e);\
        } else {\
            panel->push_back(new UI::Text(#param, createText("nullptr")));\
        }\
    });\
}

#define DEBUG_RAWTYPE(type, param, to_str) \
UI::Element* load(const type* param, std::string const& name) {\
    return param ? new UI::Text(#param, createText(name + " : " + to_str(*param)))\
                 : new UI::Text(#param, createText(name + " : nullptr"));\
}

class Debug {
public:
    Debug(Map* map = nullptr, Player* player = nullptr);
    ~Debug();

    void rebuild();

    void use (Player* player);
    void use (Map* map);
    void update();

private:
#define TO_STR_INT(i) std::to_string(i)
    DEBUG_RAWTYPE(int, i, TO_STR_INT)
    DEBUG_RAWTYPE(unsigned int, i, TO_STR_INT)
    DEBUG_RAWTYPE(float, i, TO_STR_INT)
    DEBUG_RAWTYPE(double, i, TO_STR_INT)
    DEBUG_RAWTYPE(long, i, TO_STR_INT)
#undef TO_STR_INT

    DEBUG_CLASS(Hex, hex, hex->x, hex->y)

#define MAP_DEBUG(panel, pair) \
    panel->push_back(createCollapsablePanel("hash", createText("hash <" + std::to_string(pair.first) + ">"), [&pair, this] (UI::Panel* sub_pan) {\
        sub_pan->push_back(load(&pair.second, "hex"));\
    }))
    DEBUG_CONTAINER(Map::map_has_hex, map, MAP_DEBUG)
#undef MAP_DEBUG

    DEBUG_CLASS(Map, map, map->size, map->hexs)

    DEBUG_CLASS(Player, player, *player->hex)


    sf::Text createText(sf::String const& str);
    UI::Panel* createCollapsablePanel(std::string const& name, sf::Text title, std::function<void(UI::Panel*)> onClickFunc);

    Map* map;
    Player* player;

    sf::RenderWindow window;
    UI ui;
};

#endif