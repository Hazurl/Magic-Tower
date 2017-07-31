#include <Utilities/GameRenderer.h>

float GameRenderer::HEIGHT_HEX_PIXELS = 50;
float GameRenderer::WIDTH_HEX_PIXELS = GameRenderer::HEIGHT_HEX_PIXELS * sqrt(3) / 2;

float GameRenderer::HEIGHT_UNIT_PIXELS = GameRenderer::HEIGHT_HEX_PIXELS * 0.50f;
float GameRenderer::WIDTH_UNIT_PIXELS = GameRenderer::HEIGHT_UNIT_PIXELS;

GameRenderer::GameRenderer() {
    RessourcesLoader::load<sf::Texture>("hex_ground", "image/Ground.png");
    RessourcesLoader::load<sf::Texture>("hex_wall", "image/wall.png");
    RessourcesLoader::load<sf::Texture>("hex_lava", "image/lava.png");

    RessourcesLoader::load<sf::Texture>("unit_player", "image/hat.png");
    RessourcesLoader::load<sf::Texture>("unit_enemy", "image/warrior.png");

    RessourcesLoader::load<sf::Font>("roboto", "Font/Roboto-Regular.ttf");
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
    if (gs.getSelectedHex())
        renderOnHexLayer(window, gs.getSelectedHex(), gs.getCamera());
    renderUnitLayer(window, gs.getUnits(), gs.getCamera());
}

void GameRenderer::renderOnHexLayer(sf::RenderWindow& window, const SelectedHex* sHex, Camera const& camera) {
        float thickness = 2 * camera.getZoom();
        float radius = GameRenderer::HEIGHT_HEX_PIXELS * camera.getZoom() / 2.f;

        sf::CircleShape hexa1(radius * 0.75f, 6);
        hexa1.setOrigin(radius * 0.75f, radius * 0.75f);;

        hexa1.setFillColor(sf::Color::Transparent);
        hexa1.setOutlineColor(sHex->getColor());
        hexa1.setOutlineThickness(thickness);
        hexa1.setRotation(sHex->getRotation());

        sf::CircleShape hexa2(radius * 0.50f, 6);
        hexa2.setOrigin(radius * 0.50f, radius * 0.50f);;

        hexa2.setFillColor(sf::Color::Transparent);
        hexa2.setOutlineColor(sHex->getColor());
        hexa2.setOutlineThickness(thickness);
        hexa2.setRotation(-sHex->getRotation());
        
        // Position sur la map
        int x_axes = sHex->getHex()->getX();
        int y_axes = sHex->getHex()->getY();

        // Position relative du centre de la cellule en pixel par rapport au centre de l'ecran
        auto relativePos = getPositionHexRelativeToOrigin(x_axes, y_axes, camera.getZoom());

        // Origine de l'ecran
        auto screenOrigin = getScreenOrigin(window.getSize(), camera.getPositionX(), camera.getPositionY());

        hexa1.setPosition( relativePos.x + screenOrigin.x, 
                           relativePos.y + screenOrigin.y);

        window.draw(hexa1);
        hexa2.setPosition( relativePos.x + screenOrigin.x, 
                           relativePos.y + screenOrigin.y);

        window.draw(hexa2);
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
        float scale = (GameRenderer::HEIGHT_HEX_PIXELS * camera.getZoom()) / static_cast<float>(hex_sp.getTextureRect().height);
        hex_sp.setScale(scale, scale);

        // Taille du sprite
        auto sprite_rect = hex_sp.getGlobalBounds();

        // Position sur la map
        int x_axis = hex->getX();
        int y_axis = hex->getY();

        // Position relative du centre de la cellule en pixel par rapport au centre de l'ecran
        auto relativePos = getPositionHexRelativeToOrigin(x_axis, y_axis, camera.getZoom());

        // Origine de l'ecran
        auto screenOrigin = getScreenOrigin(window.getSize(), camera.getPositionX(), camera.getPositionY());

        hex_sp.setPosition( relativePos.x - sprite_rect.width / 2.f + screenOrigin.x, 
                            relativePos.y - sprite_rect.height / 2.f + screenOrigin.y );

        window.draw(hex_sp);
        colliders_hexes.push_back(new HexCollider(hex, relativePos.x + screenOrigin.x, 
                                                       relativePos.y + screenOrigin.y, 
                                                       GameRenderer::HEIGHT_HEX_PIXELS * camera.getZoom() / 2));


        sf::Text coordsText(std::string("(") + std::to_string(x_axis) + ", " + std::to_string(y_axis) + ")", *RessourcesLoader::get<sf::Font>("roboto"));
        coordsText.setColor(sf::Color::Blue);
        coordsText.setCharacterSize(10 * camera.getZoom());
        auto boundsText = coordsText.getLocalBounds();
        coordsText.setOrigin(boundsText.width / 2, boundsText.height / 2);
        coordsText.setPosition(relativePos.x + screenOrigin.x,  relativePos.y + screenOrigin.y );
        window.draw(coordsText);
#if DEBUG > 1
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
        float scale = (GameRenderer::HEIGHT_UNIT_PIXELS * camera.getZoom()) / static_cast<float>(unit_sp.getTextureRect().height);
        unit_sp.setScale(scale, scale);

        // Taille du sprite
        auto sprite_rect = unit_sp.getGlobalBounds();

        // Position sur la map
        int x_axes = unit->getHex()->getX();
        int y_axes = unit->getHex()->getY();

        // Position relative du centre de la cellule en pixel par rapport au centre de l'ecran
        auto relativePos = getPositionHexRelativeToOrigin(x_axes, y_axes, camera.getZoom());

        // Origine de l'ecran
        auto screenOrigin = getScreenOrigin(window.getSize(), camera.getPositionX(), camera.getPositionY());

        unit_sp.setPosition( relativePos.x - sprite_rect.width / 2.f + screenOrigin.x, 
                             relativePos.y - sprite_rect.height / 2.f + screenOrigin.y );

        window.draw(unit_sp);
        // TODO 
        /*colliders_units.push_back(new UnitCollider(unit_sp, relative_x + origin_x, 
                                                            relative_y + origin_y, 
                                                            sprite_rect.height * 0.4));*/
#if DEBUG > 1
        //colliders_hexes.back()->draw(window);
#endif
    }
}

sf::Vector2f GameRenderer::getPositionHexRelativeToOrigin (int x, int y, float camera_zoom) {
    return { (x + y / 2.f) * GameRenderer::WIDTH_HEX_PIXELS  * camera_zoom,
               (y * 0.75f) * GameRenderer::HEIGHT_HEX_PIXELS * camera_zoom };
}

sf::Vector2f GameRenderer::getScreenOrigin (sf::Vector2u const& screenSize, float camera_x, float camera_y) {
    return { screenSize.x / 2.f + camera_x,
             screenSize.y / 2.f + camera_y };
}