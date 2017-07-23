#include "../../Header/Utilities/GameRenderer.h"

float GameRenderer::WIDTH_HEX = sqrt(3) / 2;

GameRenderer::GameRenderer() {
    RessourcesLoader::load<sf::Texture>("hex_ground", "image/Ground.png");
    RessourcesLoader::load<sf::Texture>("hex_wall", "image/wall.png");
    RessourcesLoader::load<sf::Texture>("hex_lava", "image/lava.png");

    RessourcesLoader::load<sf::Texture>("unit_player", "image/hat.png");
    RessourcesLoader::load<sf::Texture>("unit_enemy", "image/warrior.png");
}

GameRenderer::~GameRenderer() {
    clearColliders();
}

void GameRenderer::clearColliders() {
    for (auto* col : colliders_hexes)
        delete col;

    colliders_hexes.clear();
}

std::vector<const Hex*> GameRenderer::raycast_hexLayer(float x, float y) {
    std::vector<const Hex*> hexes = {};
    for (auto* collider : colliders_hexes) {
        if (collider->isColliding(x, y))
            hexes.push_back(collider->hex);
    }
    return std::move(hexes);
}

void GameRenderer::render (sf::RenderWindow& window, GameState const& gs) {
    clearColliders();

    renderHexLayer(window, gs.getHexes(), gs.getCamera());
    renderUnitLayer(window, gs.getUnits(), gs.getCamera());
}

void GameRenderer::renderHexLayer(sf::RenderWindow& window, std::vector<const Hex*> hexes, Camera const& camera) {
    for (auto* hex : hexes) {
        //Texture
        const sf::Texture* texture;
        if (hex->getType() == Hex::Type::Ground)
            texture = RessourcesLoader::get<sf::Texture>("hex_ground");
        else if (hex->getType() == Hex::Type::Lava)
            texture = RessourcesLoader::get<sf::Texture>("hex_lava");
        else if (hex->getType() == Hex::Type::Wall)
            texture = RessourcesLoader::get<sf::Texture>("hex_wall");
        else
            assert(false && ("No Texture for this hex type : " + static_cast<int>(hex->getType())));

        // Creation sprite, assignation texture et taille
        sf::Sprite hex_sp (*texture);
        float scale = (HEX_HEIGHT_PIXEL * camera.getZoom()) / static_cast<float>(hex_sp.getTextureRect().height);
        hex_sp.setScale(scale, scale);

        // Taille du sprite
        auto sprite_rect = hex_sp.getGlobalBounds();

        // Position sur la map
        int x_axes = hex->getX();
        int y_axes = hex->getY();

        // Position relative du centre de la cellule en pixel par rapport au centre de l'ecran
        float relative_x = ((x_axes + y_axes / 2.f)) * sprite_rect.width;
        float relative_y = (y_axes * 0.75) * sprite_rect.height;

        // Origine de l'ecran
        auto screen_size = window.getSize();
        float origin_x = screen_size.x / 2.f + camera.getPositionX();
        float origin_y = screen_size.y / 2.f + camera.getPositionY();

        hex_sp.setPosition( relative_x - sprite_rect.width / 2.f + origin_x, 
                            relative_y - sprite_rect.height / 2.f + origin_y );

        window.draw(hex_sp);
        colliders_hexes.push_back(new HexCollider(hex, relative_x + origin_x, 
                                                       relative_y + origin_y, 
                                                       sprite_rect.height / 2));
#if DEFINE > 1
        colliders_hexes.back()->draw(window);
#endif
    }
}

void GameRenderer::renderUnitLayer(sf::RenderWindow& window, std::vector<const Unit*> units, Camera const& camera) {
    for (auto* unit : units) {
        //Texture
        const sf::Texture* texture;
        if (dynamic_cast<const Player*>(unit))
            texture = RessourcesLoader::get<sf::Texture>("unit_player");
        else
            texture = RessourcesLoader::get<sf::Texture>("unit_enemy");

        // Creation sprite, assignation texture et taille
        sf::Sprite unit_sp (*texture);
        float scale = (UNIT_HEIGHT_PIXEL * camera.getZoom()) / static_cast<float>(unit_sp.getTextureRect().height);
        unit_sp.setScale(scale, scale);

        // Taille du sprite
        auto sprite_rect = unit_sp.getGlobalBounds();

        // Position sur la map
        int x_axes = unit->getHex()->getX();
        int y_axes = unit->getHex()->getY();

        // Position relative du centre de la cellule en pixel par rapport au centre de l'ecran
        float relative_x = ((x_axes + y_axes / 2.f)) * sprite_rect.width;
        float relative_y = (y_axes * 0.75) * sprite_rect.height;

        // Origine de l'ecran
        auto screen_size = window.getSize();
        float origin_x = screen_size.x / 2.f + camera.getPositionX();
        float origin_y = screen_size.y / 2.f + camera.getPositionY();

        unit_sp.setPosition( relative_x - sprite_rect.width / 2.f + origin_x, 
                             relative_y - sprite_rect.height / 2.f + origin_y );

        window.draw(unit_sp);
        // TODO 
        /*colliders_units.push_back(new UnitCollider(unit_sp, relative_x + origin_x, 
                                                            relative_y + origin_y, 
                                                            sprite_rect.height * 0.4));*/
#if DEFINE > 1
        //colliders_hexes.back()->draw(window);
#endif
    }
}
