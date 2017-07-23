#ifndef __DEBUG
#define __DEBUG

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <map>

#include "RessourcesLoader.h"
#include "DebugMacro.h"
#include "../GameState/GameState.h"
#include "../GameState/Map.h"
#include "../GameState/Hex.h"
#include "../GameState/Player.h"
#include "../GameState/Camera.h"
#include "Input.h"
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
    Debug(GameState* gameState = nullptr, Input* input = nullptr);
    ~Debug();

    void rebuild();

    void use (GameState* gameState);
    void use (Input* input);
    void update();

private:
#define TO_STR_NUM(i) std::to_string(i)
    DEBUG_RAWTYPE(int, i, TO_STR_NUM)
    DEBUG_RAWTYPE(unsigned int, i, TO_STR_NUM)
    DEBUG_RAWTYPE(float, i, TO_STR_NUM)
    DEBUG_RAWTYPE(double, i, TO_STR_NUM)
    DEBUG_RAWTYPE(long, i, TO_STR_NUM)
#undef TO_STR_NUM

#define TO_STR_BUTTON(b) Input::to_string(b)
    DEBUG_RAWTYPE(Input::Button, but, TO_STR_BUTTON)
    DEBUG_RAWTYPE(Input::ButtonState, but, TO_STR_BUTTON)
#undef TO_STR_BUTTON

#define TO_STR_HEX_TYPE(t) Hex::to_string(t)
    DEBUG_RAWTYPE(Hex::Type, type, TO_STR_HEX_TYPE)
#undef TO_STR_BUTTON

    DEBUG_CLASS(Hex, hex, hex->x, hex->y, hex->type)

#define MAP_DEBUG(panel, pair) \
    panel->push_back(createCollapsablePanel("hash", createText("hash <" + TO_STR_KEY(pair.first) + ">"), [&pair, this] (UI::Panel* sub_pan) {\
        sub_pan->push_back(load(&pair.second, "hex"));\
    }))

#define TO_STR_KEY(l) std::to_string(l)
    typedef std::map<long, HexGO> map_hash_hex;
    DEBUG_CONTAINER(map_hash_hex, map, MAP_DEBUG)
#undef TO_STR_KEY

#define TO_STR_KEY(b) Input::to_string(b)
    typedef std::map<Input::Button, Input::ButtonState> input_button_state;
    DEBUG_CONTAINER(input_button_state, map, MAP_DEBUG)
#undef TO_STR_KEY
#undef MAP_DEBUG

    DEBUG_CLASS(Map, map, map->size, map->hexes)

    DEBUG_CLASS(Camera, camera, camera->x, camera->y, camera->zoom)

    DEBUG_CLASS(Player, player, *player->hex)

    DEBUG_CLASS(Input, input, input->inputs, input->mouseX, input->mouseY, input->scroll)

    DEBUG_CLASS(GameState, gameState, gameState->map, *gameState->player, gameState->camera)


    sf::Text createText(sf::String const& str);
    UI::Panel* createCollapsablePanel(std::string const& name, sf::Text title, std::function<void(UI::Panel*)> onClickFunc);

    GameState* gameState;
    Input* input;

    sf::RenderWindow window;
    UI ui;
};

#endif