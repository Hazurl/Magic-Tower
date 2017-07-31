#include <GameState/GameState.h>

GameState::GameState() : map(8), player(new PlayerGO(map.getHexAt(0, 0))), enemies({}), selectedHex(nullptr) {
    auto hexes = ReachableHexes::find(map, map.getHexAt(0, 0), 5);
    for (auto& pair : hexes) {
        actionHexes.push_back(pair.first);
    }
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

void GameState::updateInputs(UpdateInfo const& infos) {
    if (infos.inputs.isPressed(Input::Button::MouseLeft)) {
        start_mouse_pos = last_mouse_pos = infos.inputs.getMousePosition();
    }
    else if (infos.inputs.isDown(Input::Button::MouseLeft)) {
        sf::Vector2f current_mouse_pos = infos.inputs.getMousePosition();
        
        camera.move(current_mouse_pos.x - last_mouse_pos.x, current_mouse_pos.y - last_mouse_pos.y );

        last_mouse_pos = current_mouse_pos;
    }

    if (infos.inputs.getScroll() != 0) {
        camera.moveZoom(infos.inputs.getScroll());
    }

    if (!infos.RayCast_Hex.empty() && infos.inputs.isRealeased(Input::Button::MouseLeft) && start_mouse_pos == infos.inputs.getMousePosition()) {
        setSelectedHex(infos.RayCast_Hex[0]);
    }

    switch (state) {
        case State::PlayerTurn :
            updatePlayerTurn(infos);
            break;
        case State::Action_1:
            actionHexes = player->getPossibleActionHexes(map, 0);
            state = State::PlayerTurn;
            break;
        case State::Action_2:
            actionHexes = player->getPossibleActionHexes(map, 1);
            state = State::PlayerTurn;
            break;
        case State::Action_3:
            actionHexes = player->getPossibleActionHexes(map, 2);
            state = State::PlayerTurn;
            break;
        default:
            break;
    }
}

void GameState::updateAnimations (float deltaTime) {
    if (selectedHex)
        selectedHex->updateAnimations(deltaTime);
}

void GameState::updatePlayerTurn(UpdateInfo const& infos) {
    if (infos.inputs.isPressed(Input::Button::Action_1)) {
        state = State::Action_1;
    }
    else if (infos.inputs.isPressed(Input::Button::Action_2)) {
        state = State::Action_2;
    }
    else if (infos.inputs.isPressed(Input::Button::Action_3)) {
        state = State::Action_3;
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

std::vector<const Hex*> GameState::getPossibleActionHexes() const {
    return actionHexes;
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
