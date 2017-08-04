#ifndef __GAMESTATE
#define __GAMESTATE

#include <GameState/Map.h>
#include <GameState/Camera.h>

#include <GameObject/PlayerGO.h>
#include <GameObject/SelectedHex.h>
#include <GameObject/EnemyGO.h>
#include <Utilities/DebugMacro.h>
#include <Utilities/Input.h>
#include <Utilities/Pathfinding.h>
#include <Utilities/ReachableHexes.h>

class GameState {
    GIVE_ACCESS_DEBUG()

public:
    struct UpdateInfo {
        const Input inputs;
        const std::vector<const Hex*> RayCast_Hex;
        const std::vector<const Unit*> RayCast_Unit;
        //const std::vector<const UI*> RayCast_UI;
    };

    GameState();
    ~GameState();

    void updateInputs(UpdateInfo const& infos);
    void updateAnimations(float deltaTime);

    std::vector<const Hex*> getHexes() const;
    std::vector<const Unit*> getUnits() const;
    const SelectedHex* getSelectedHex () const;
    std::vector<const Hex*> getPossibleActionHexes() const;
    std::vector<const Hex*> getReachableHexes() const;
    std::vector<const Hex*> getLowPath() const;
    std::vector<const Hex*> getHighPath() const;
    const Camera& getCamera() const;

private:
    Map map;
    PlayerGO* player;
    std::vector<Enemy*> enemies = {};

    Camera camera;
    sf::Vector2f last_mouse_pos;
    sf::Vector2f start_mouse_pos;

    void setSelectedHex(const Hex* hex);
    SelectedHex* selectedHex = nullptr;

    std::vector<const Hex*> reachableHexes = {};

    void updateCamera(UpdateInfo const& infos);
    void updateSelectedHex(UpdateInfo const& infos);

    void nextTurn();
    bool is_player_turn;

    /* Player Turn */
    enum class PlayerState {
        Waiting, Move, Action_1, Action_2, Action_3
    };

    void updatePlayerTurn(UpdateInfo const& infos);

    PlayerState playerState_on_start = PlayerState::Waiting;
    PlayerState playerState;
    int MP;
    std::vector<const Hex*> path = {};
    std::vector<const Hex*> actionHexes = {};

    void playerOnWaiting(UpdateInfo const& infos);
    void playerOnMove(UpdateInfo const& infos);
    void playerOnAction(UpdateInfo const& infos);


    /* Enemies Turn */
    void updateEnemiesTurn(UpdateInfo const& infos);
};

#endif