#include "../../Header/GameState/GameState.h"

GameState::GameState() : map(8), player(new PlayerGO(map.getHexAt(1, 2))), enemies({ new EnemyGO(map.getHexAt(0, 3)) }) {
    
}

GameState::~GameState() {
    if (player)
        delete player;

    for (auto* e : enemies)
        delete e;
    enemies.clear();
}

void GameState::update(Input const& inputs, std::vector<const Hex*> const& RC_hexes) {
    if (inputs.isPressed(Input::Button::MouseLeft)) {
        last_mouse_pos = { inputs.getMouseX(), inputs.getMouseY() };
    }
    else if (inputs.isDown(Input::Button::MouseLeft)) {
        sf::Vector2f current_mouse_pos = { inputs.getMouseX(), inputs.getMouseY() };
        
        camera.move(current_mouse_pos.x - last_mouse_pos.x, current_mouse_pos.y - last_mouse_pos.y );

        last_mouse_pos = current_mouse_pos;
    }

    if (inputs.getScroll() != 0) {
        camera.moveZoom(inputs.getScroll());
    }
}

std::vector<const Hex*> GameState::getHexes() const {
    std::vector<const Hex*> hexes = {};

    for (auto* hex_go : map.getHexes())
        hexes.push_back(hex_go);

    return std::move(hexes);
}

std::vector<const Unit*> GameState::getUnits() const {
    std::vector<const Unit*> units = {};
    if (player)
        units.push_back(player);

    for (auto* e : enemies)
        units.push_back(e);

    return std::move(units);
}

const Camera& GameState::getCamera() const {
    return camera;
}

