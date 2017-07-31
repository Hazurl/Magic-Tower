#ifndef __GAME_RENDERER
#define __GAME_RENDERER

#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>
#include <string>

#include <Utilities/Constant.h>
#include <Utilities/RessourcesLoader.h>

#include <GameState/GameState.h>
#include <GameState/Camera.h>
#include <GameState/Unit.h>
#include <GameState/Hex.h>

#include <Collider/Collider.h>
#include <Collider/HexCollider.h>

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
    void renderOnHexLayer(sf::RenderWindow& window, const SelectedHex* sHex, Camera const& camera);
    void renderUnitLayer(sf::RenderWindow& window, std::vector<const Unit*> units, Camera const& camera);

    sf::Vector2f getPositionHexRelativeToOrigin (int x, int y, float camera_zoom);
    sf::Vector2f getScreenOrigin (sf::Vector2u const& screenSize, float camera_x, float camera_y);

    std::vector<HexCollider*> colliders_hexes;
    //std::vector<UnitCollider*> colliders_unit;

    static float WIDTH_HEX_PIXELS;
    static float HEIGHT_HEX_PIXELS;

    static float HEIGHT_UNIT_PIXELS;
    static float WIDTH_UNIT_PIXELS;

};

#endif