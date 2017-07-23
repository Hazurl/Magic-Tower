#ifndef __GAMESTATE
#define __GAMESTATE

#include "Map.h"
#include "Camera.h"

#include "../GameObject/PlayerGO.h"
#include "../GameObject/EnemyGO.h"
#include "../Utilities/DebugMacro.h"
#include "../Utilities/Input.h"

class GameState {
    GIVE_ACCESS_DEBUG()
    
public:
    GameState();
    ~GameState();

    void update(Input const& inputs, std::vector<const Hex*> const& RC_hexes);

    std::vector<const Hex*> getHexes() const;
    std::vector<const Unit*> getUnits() const;
    const Camera& getCamera() const;

private:
    Map map;
    PlayerGO* player;
    std::vector<Enemy*> enemies = {};

    Camera camera;
    sf::Vector2f last_mouse_pos;
};

#endif