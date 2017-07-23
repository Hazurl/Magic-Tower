#ifndef __GAME_RENDERER
#define __GAME_RENDERER

#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>

#include "Constant.h"
#include "RessourcesLoader.h"

#include "../GameState/GameState.h"
#include "../GameState/Camera.h"
#include "../GameState/Unit.h"
#include "../GameState/Hex.h"

#include "../Collider/Collider.h"
#include "../Collider/HexCollider.h"

class GameRenderer {
public:
    GameRenderer();
    ~GameRenderer();

    void clearColliders();

    std::vector<const Hex*> raycast_hexLayer (float x, float y);
    //std::vector<const Unit*> raycast_unitLayer (float x, float y);

    void render (sf::RenderWindow& window, GameState const& gs);

private:
    void renderHexLayer(sf::RenderWindow& window, std::vector<const Hex*> hexes, Camera const& camera);
    void renderUnitLayer(sf::RenderWindow& window, std::vector<const Unit*> units, Camera const& camera);

    std::vector<HexCollider*> colliders_hexes;
    //std::vector<UnitCollider*> colliders_unit;

    static float WIDTH_HEX;

};

#endif