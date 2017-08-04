#include <GameState/GameState.h>

GameState::GameState() : map(8), player(nullptr), enemies({}), selectedHex(nullptr) {
    // Find player position
    auto possibleHexes = map.filterHexes([] (const Hex* h) { return h->getType() == Hex::Type::Ground; });
    player = new PlayerGO(possibleHexes[static_cast<int>(rand() % possibleHexes.size())]);

    is_player_turn = false;
    nextTurn();
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
    updateCamera(infos);
    updateSelectedHex(infos);

    if (is_player_turn)
        updatePlayerTurn(infos);
    else
        updateEnemiesTurn(infos);
}

void GameState::nextTurn() {
    if (is_player_turn) {
        is_player_turn = false;
    } else {
        is_player_turn = true;
        std::cout << "Waiting" << std::endl;
        playerState = playerState_on_start;
    }
}


void GameState::updateAnimations (float deltaTime) {
    if (selectedHex)
        selectedHex->updateAnimations(deltaTime);
}

void GameState::updateCamera(UpdateInfo const& infos) {
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
}

void GameState::updateSelectedHex(UpdateInfo const& infos) {
    if (!infos.RayCast_Hex.empty() && infos.inputs.isReleased(Input::Button::MouseLeft) && start_mouse_pos == infos.inputs.getMousePosition()) {
        std::cout << "Set Selected Hex : " << infos.RayCast_Hex[0] << std::endl;
        setSelectedHex(infos.RayCast_Hex[0]);
    } else
        setSelectedHex(nullptr);
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
    for (int i = 0; i <= MP && i < static_cast<int>(path.size()); ++i) {
        low_path.push_back(path[i]);
    }
    return low_path;
}

std::vector<const Hex*> GameState::getHighPath() const {
    std::vector<const Hex*> high_path = {};
    for (int i = MP; i < static_cast<int>(path.size()); ++i) {
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
