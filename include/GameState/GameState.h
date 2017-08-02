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

    enum class State {
        PlayerTurn, Action_1, Action_2, Action_3, Move, EnemiesTurn//, Wait
    };
/* IDEA ?
    function<bool(void)> waiting_until = nullptr;
    State next;
*/
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
    State state;

    Camera camera;
    sf::Vector2f last_mouse_pos;
    sf::Vector2f start_mouse_pos;

    void setSelectedHex(const Hex* hex);
    SelectedHex* selectedHex = nullptr;

    std::vector<const Hex*> path = {};
    std::vector<const Hex*> actionHexes = {};
    std::vector<const Hex*> reachableHexes = {};

    void updatePlayerTurn(UpdateInfo const& infos);
};

#endif