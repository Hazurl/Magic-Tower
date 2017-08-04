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
    void renderHexLayer(std::vector<const Hex*> hexes);
    void renderActionHexes(std::vector<const Hex*> hexes);
    void renderReachableHexes(std::vector<const Hex*> hexes);
    void renderPath(std::vector<const Hex*> hexes, bool is_accessible);
    void renderSelectedHex(const SelectedHex* sHex);
    void renderUnitLayer(std::vector<const Unit*> units);

    sf::Vector2f getPositionHexRelativeToOrigin (int x, int y);
    sf::Vector2f getScreenOrigin();
    sf::Vector2f getHexPosition(int x, int y);

    sf::CircleShape createHexShape(int x, int y, float thickness, float size, sf::Color boundsColor);
    sf::Sprite createSprite(int x, int y, sf::Texture const& texture, float heightPixels = GameRenderer::HEIGHT_HEX_PIXELS);
    sf::Text createText(sf::Vector2f const& pos, sf::String const& str, std::string const& font, sf::Color const& color, unsigned int size, bool proportional_to_zoom = true);
    sf::Text createText(float screenX, float screenY, sf::String const& str, std::string const& font, sf::Color const& color, unsigned int size, bool proportional_to_zoom = true);

    void drawLine(sf::Vector2f const& begin, sf::Vector2f const& end, float thickness, sf::Color const& color);

    const sf::Texture& getHexTexture(Hex::Type type);
    const sf::Texture& getUnitTexture(bool is_player);

    std::vector<HexCollider*> colliders_hexes = {};
    //std::vector<UnitCollider*> colliders_unit;

    static float WIDTH_HEX_PIXELS;
    static float HEIGHT_HEX_PIXELS;

    static float HEIGHT_UNIT_PIXELS;
    static float WIDTH_UNIT_PIXELS;

    sf::RenderWindow* window = nullptr;
    const Camera* camera = nullptr;
    sf::Vector2f origin;

};

#endif