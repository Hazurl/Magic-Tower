/*#include <GameState/GameState.h>

void GameState::updatePlayerTurn(UpdateInfo const& infos) {
    path = {};
    actionHexes = {};

    switch(playerState) {
        case PlayerState::Waiting:
            playerOnWaiting(infos);
            break;
        case PlayerState::Move:
            playerOnMove(infos);
            break;
        case PlayerState::Action_1:
        case PlayerState::Action_2:
        case PlayerState::Action_3:
            playerOnAction(infos);
            break;
    }
}

void GameState::playerOnWaiting(UpdateInfo const& infos) {
    if (Input::isPressed(Input::Button::Action_1)) {
        actionHexes = player->getPossibleActionHexes(map, 0);
        std::cout << "Action_1" << std::endl;
        playerState = PlayerState::Action_1;
    }
    else if (Input::isPressed(Input::Button::Action_2)) {
        actionHexes = player->getPossibleActionHexes(map, 1);
        std::cout << "Action_2" << std::endl;
        playerState = PlayerState::Action_2;
    }
    else if (Input::isPressed(Input::Button::Action_3)) {
        actionHexes = player->getPossibleActionHexes(map, 2);
        std::cout << "Action_3" << std::endl;
        playerState = PlayerState::Action_3;
    } else {
        MP = player->getMP();
        playerOnMove(infos);
    }
}

void GameState::playerOnMove(UpdateInfo const& infos) {
    if (!infos.RayCast_Hex.empty()) {
        PathFinding::find(map, player->getHex(), infos.RayCast_Hex[0], path);
    }

    if (selectedHex) {
        std::vector<const Hex*> p = {};
        auto idx = std::distance(path.begin(), std::find(path.begin(), path.end(), selectedHex->getHex()));
        if (idx >= MP) {
            idx = MP;
            
            nextTurn();
        }

        MP -= idx;

        player->setHex(path[idx]);

        std::cout << "Move" << std::endl;
        playerState = PlayerState::Move;
    }
}

void GameState::playerOnAction(UpdateInfo const& infos) {
    if (Input::isPressed(Input::Button::Action_1)) {
        playerState = playerState == PlayerState::Action_1 ? PlayerState::Waiting : PlayerState::Action_1;
        return;

    } else if (Input::isPressed(Input::Button::Action_2)) {
        playerState = playerState == PlayerState::Action_2 ? PlayerState::Waiting : PlayerState::Action_2;
        return;

    } else if (Input::isPressed(Input::Button::Action_3)) {
        playerState = playerState == PlayerState::Action_3 ? PlayerState::Waiting : PlayerState::Action_3;
        return;
        
    } else if (Input::isPressed(Input::Button::Escape)) {
        playerState = PlayerState::Waiting;
        return;
    }
    
    switch(playerState) {
        case PlayerState::Action_1:
            actionHexes = player->getPossibleActionHexes(map, 0);
            break;

        case PlayerState::Action_2:
            actionHexes = player->getPossibleActionHexes(map, 1);
            break;

        case PlayerState::Action_3:
            actionHexes = player->getPossibleActionHexes(map, 2);
            break;

        default: assert(false);
    }

    if (selectedHex) {
        auto it_to_hex = std::find(actionHexes.begin(), actionHexes.end(), selectedHex->getHex());
        if (it_to_hex != actionHexes.end()) {
            switch(playerState) {
                case PlayerState::Action_1:
                    player->doAction(map, 0, *it_to_hex);
                    break;

                case PlayerState::Action_2:
                    player->doAction(map, 1, *it_to_hex);
                    break;

                case PlayerState::Action_3:
                    player->doAction(map, 2, *it_to_hex);
                    break;

                default: assert(false);
            }

            nextTurn();
        }
    }
}
*/