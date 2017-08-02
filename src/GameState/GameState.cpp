#include <GameState/GameState.h>

GameState::GameState() : map(8), player(nullptr), enemies({}), state(State::Move), selectedHex(nullptr) {
    // Find player position
    auto possibleHexes = map.filterHexes([] (const Hex* h) { return h->getType() == Hex::Type::Ground; });
    player = new PlayerGO(possibleHexes[static_cast<int>(rand() % possibleHexes.size())]);
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

    if (!infos.RayCast_Hex.empty() && infos.inputs.isReleased(Input::Button::MouseLeft) && start_mouse_pos == infos.inputs.getMousePosition()) {
        setSelectedHex(infos.RayCast_Hex[0]);
    } else {
        setSelectedHex(nullptr);
    }

    switch (state) {
        case State::Move :
        case State::Action_1:
        case State::Action_2:
        case State::Action_3:
            updatePlayerTurn(infos);
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
        actionHexes = player->getPossibleActionHexes(map, 1);
    }
    else if (infos.inputs.isPressed(Input::Button::Action_2)) {
        state = State::Action_2;
        actionHexes = player->getPossibleActionHexes(map, 2);
    }
    else if (infos.inputs.isPressed(Input::Button::Action_3)) {
        state = State::Action_3;
        actionHexes = player->getPossibleActionHexes(map, 3);
    }
    else {
        if (!infos.RayCast_Hex.empty()) {
            PathFinding::find(map, player->getHex(), infos.RayCast_Hex[0], path);
        } else {
            path = {};
        }

        if (selectedHex) {
            std::vector<const Hex*> p = {};
            auto idx = std::distance(path.begin(), std::find(path.begin(), path.end(), selectedHex->getHex()));
            if (idx > player->getMP())
                idx = player->getMP();
            player->setHex(path[idx]);
        }
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

std::vector<const Hex*> GameState::getReachableHexes() const {
    return reachableHexes;
}

std::vector<const Hex*> GameState::getLowPath() const {
    std::vector<const Hex*> low_path = {};
    for (int i = 0; i <= player->getMP() && i < static_cast<int>(path.size()); ++i) {
        low_path.push_back(path[i]);
    }
    return low_path;
}

std::vector<const Hex*> GameState::getHighPath() const {
    std::vector<const Hex*> high_path = {};
    for (int i = player->getMP(); i < static_cast<int>(path.size()); ++i) {
        high_path.push_back(path[i]);
    }
    return high_path;
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
