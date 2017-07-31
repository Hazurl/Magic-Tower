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

class GameState {
    GIVE_ACCESS_DEBUG()
    
public:
    GameState();
    ~GameState();

    void updateInputs(Input const& inputs, std::vector<const Hex*> const& RC_hexes);
    void updateAnimations(float deltaTime);

    std::vector<const Hex*> getHexes() const;
    std::vector<const Unit*> getUnits() const;
    const SelectedHex* getSelectedHex () const;
    const Camera& getCamera() const;

private:
    Map map;
    PlayerGO* player;
    std::vector<Enemy*> enemies = {};

    Camera camera;
    sf::Vector2f last_mouse_pos;

    void setSelectedHex(const Hex* hex);
    SelectedHex* selectedHex = nullptr;

    std::vector<const Hex*> path = {};
};

#endif