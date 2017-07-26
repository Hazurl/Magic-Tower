#include <GameState/GameState.h>

GameState::GameState() : map(8), player(nullptr), enemies({}), selectedHex(nullptr) {
    PathFinding pathF(&map);

    std::vector<const Hex*> path = {};
    if (pathF.getPath(map.getHexAt(0, 0), map.getHexAt(5, -5), path)) {
        std::cout << "Path : " << std::endl;
        for (const Hex* hex : path) {
            std::cout << "Hex (" << hex->getX() << ", " << hex->getY() << ")" << std::endl;
        }
    }
    else std::cout << "No path" << std::endl;
}

GameState::~GameState() {
    if (player)
        delete player;

    for (auto* e : enemies)
        delete e;
    enemies.clear();

    if (selectedHex)
        delete selectedHex;
}

void GameState::updateInputs(Input const& inputs, std::vector<const Hex*> const& RC_hexes) {
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

    if (!RC_hexes.empty() && inputs.isRealeased(Input::Button::MouseLeft) && last_mouse_pos == sf::Vector2f({ inputs.getMouseX(), inputs.getMouseY() })) {
        setSelectedHex(RC_hexes[0]);
    }
}

void GameState::updateAnimations (float deltaTime) {
    if (selectedHex)
        selectedHex->updateAnimations(deltaTime);
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

const SelectedHex* GameState::getSelectedHex () const {
    return selectedHex;
}

const Camera& GameState::getCamera() const {
    return camera;
}


void GameState::setSelectedHex(const Hex* hex) {
    if (selectedHex)
        delete selectedHex;
    if (hex)
        selectedHex = new SelectedHex(hex);
    else
        selectedHex = nullptr;
}
