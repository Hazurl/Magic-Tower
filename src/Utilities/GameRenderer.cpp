#include <Utilities/GameRenderer.h>
/*
float GameRenderer::HEIGHT_HEX_PIXELS = 50;
float GameRenderer::WIDTH_HEX_PIXELS = GameRenderer::HEIGHT_HEX_PIXELS * sqrt(3) / 2;

float GameRenderer::HEIGHT_UNIT_PIXELS = GameRenderer::HEIGHT_HEX_PIXELS * 0.75f;
float GameRenderer::WIDTH_UNIT_PIXELS = GameRenderer::HEIGHT_UNIT_PIXELS;

GameRenderer::GameRenderer() {
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
    return hexes;
}

void GameRenderer::render (sf::RenderWindow& window, GameState const& gs) {
    clearColliders();

    this->camera = &gs.getCamera();
    this->window = &window;

    auto screenSize = window.getSize();
    origin = { screenSize.x / 2.f + camera->getPositionX(), screenSize.y / 2.f + camera->getPositionY() };

    renderHexLayer(gs.getHexes());
    renderActionHexes(gs.getPossibleActionHexes());
    renderReachableHexes(gs.getReachableHexes());
    renderPath(gs.getLowPath(), true);
    renderPath(gs.getHighPath(), false);

    if (gs.getSelectedHex())
        renderSelectedHex(gs.getSelectedHex());
        
    renderUnitLayer(gs.getUnits());
}

void GameRenderer::renderActionHexes(std::vector<const Hex*> hexes) {
    for (const Hex* hex : hexes) {
        window->draw( createHexShape(hex->getX(), hex->getY(), 2, 1, sf::Color::Black) );
    }
}

void GameRenderer::renderReachableHexes(std::vector<const Hex*> hexes) {
    for (const Hex* hex : hexes) {
        window->draw( createHexShape(hex->getX(), hex->getY(), 2, 1, sf::Color::Blue) );
    }
}

void GameRenderer::renderPath(std::vector<const Hex*> hexes, bool is_accessible) {
    if (hexes.empty())
        return;

    sf::Color color = sf::Color::Red;
    color.a = (is_accessible ? 255 : 100);


    const Hex* prev = hexes[0];
    for (unsigned int i = 1; i < hexes.size(); ++i) {
        const Hex* cur = hexes[i];

        drawLine(getHexPosition(prev->getX(), prev->getY()), getHexPosition(cur->getX(), cur->getY()), 20, color);
        prev = cur;
    }
}

void GameRenderer::renderSelectedHex(const SelectedHex* sHex) {
    /*auto hexa1 = createHexShape(sHex->getHex()->getX(), sHex->getHex()->getY(), 2, 0.75, sHex->getColor());
    auto hexa2 = createHexShape(sHex->getHex()->getX(), sHex->getHex()->getY(), 2, 0.50, sHex->getColor());

    hexa1.setRotation(sHex->getRotation());
    hexa2.setRotation(-sHex->getRotation());

    window->draw(hexa1);
    window->draw(hexa2);
}

void GameRenderer::renderHexLayer(std::vector<const Hex*> hexes) {
    for (auto* hex : hexes) {
        sf::Sprite sp = createSprite(hex->getX(), hex->getY(), getHexTexture(hex->getType()));
        window->draw(sp);
        colliders_hexes.push_back(new HexCollider(hex, sp.getPosition().x, sp.getPosition().y, GameRenderer::HEIGHT_HEX_PIXELS / 2 * camera->getZoom()));

        sf::Text coordsText = createText(getHexPosition(hex->getX(), hex->getY()), std::string("(") + std::to_string(hex->getX()) + ", " + std::to_string(hex->getY()) + ")", "roboto", sf::Color::Blue, 10);
        window->draw(coordsText);

#if DEBUG > 1
        colliders_hexes.back()->draw(*window, *camera);
#endif
    }
}

void GameRenderer::renderUnitLayer(std::vector<const Unit*> units) {
    for (auto* unit : units) {
        auto sp = createSprite(unit->getHex()->getX(), unit->getHex()->getY(), getUnitTexture(dynamic_cast<const Player*>(unit) != nullptr), GameRenderer::HEIGHT_UNIT_PIXELS);
        window->draw(sp);
        // TODO 
        /*colliders_units.push_back(new UnitCollider(unit_sp, relative_x + origin_x, 
                                                            relative_y + origin_y, 
                                                            sprite_rect.height * 0.4));
#if DEBUG > 1
        //colliders_hexes.back()->draw(window, *camera);
#endif
    }
}

sf::Vector2f GameRenderer::getPositionHexRelativeToOrigin (int x, int y) {
    return { (x + y / 2.f) * GameRenderer::WIDTH_HEX_PIXELS  * camera->getZoom(),
               (y * 0.75f) * GameRenderer::HEIGHT_HEX_PIXELS * camera->getZoom() };
}

sf::Vector2f GameRenderer::getScreenOrigin () {
    return origin;
}

sf::Vector2f GameRenderer::getHexPosition (int x, int y) {
    return getPositionHexRelativeToOrigin(x, y) + getScreenOrigin();
}

sf::CircleShape GameRenderer::createHexShape (int x, int y, float thickness, float size, sf::Color boundsColor) {
    float screenThick = thickness * camera->getZoom();
    float radius = GameRenderer::HEIGHT_HEX_PIXELS * camera->getZoom() / 2.f * size;

    sf::CircleShape hexa(radius, 6);
    hexa.setOrigin(radius, radius);

    hexa.setFillColor(sf::Color::Transparent);
    hexa.setOutlineColor(boundsColor);
    hexa.setOutlineThickness(screenThick);

    hexa.setPosition( getPositionHexRelativeToOrigin(x, y) + getScreenOrigin() );

    return hexa;
}

const sf::Texture& GameRenderer::getHexTexture(Hex::Type type) {
    if (type == Hex::Type::Ground)
        return *TextureLoader::getGlobal("hex_ground");
    else if (type == Hex::Type::Lava)
        return *TextureLoader::getGlobal("hex_lava");
    else if (type == Hex::Type::Wall)
        return *TextureLoader::getGlobal("hex_wall");

    assert(false);
}

sf::Sprite GameRenderer::createSprite(int x, int y, sf::Texture const& texture, float heightPixels) {
    sf::Sprite sp (texture);
    auto rect = sp.getTextureRect();
    float scale = (heightPixels * camera->getZoom()) / static_cast<float>(rect.height);
    sp.setScale(scale, scale);
    sp.setOrigin(rect.width / 2, rect.height / 2);
    sp.setPosition( getPositionHexRelativeToOrigin(x, y) + getScreenOrigin() );

    return sp;    
}

const sf::Texture& GameRenderer::getUnitTexture(bool is_player) {
    if (is_player)
        return *TextureLoader::getGlobal("unit_player");
    else
        return *TextureLoader::getGlobal("unit_enemy");

    assert(false);
}

inline sf::Text GameRenderer::createText(sf::Vector2f const& pos, sf::String const& str, std::string const& font, sf::Color const& color, unsigned int size, bool proportional_to_zoom) {
    return createText(pos.x, pos.y, str, font, color, size, proportional_to_zoom);
}

sf::Text GameRenderer::createText(float screenX, float screenY, sf::String const& str, std::string const& font, sf::Color const& color, unsigned int size, bool proportional_to_zoom) {
    sf::Text text(str, *FontLoader::getGlobal(font));
    text.setColor(color);
    if (proportional_to_zoom)
        size *= camera->getZoom();
    text.setCharacterSize(size);
    auto boundsText = text.getLocalBounds();
    text.setOrigin(boundsText.width / 2, boundsText.height / 2);
    text.setPosition(screenX, screenY);

    return text;
}

void GameRenderer::drawLine(sf::Vector2f const& begin, sf::Vector2f const& end, float thickness, sf::Color const& color) {
    sf::Vertex vertices[4];

    sf::Vector2f dir = begin - end;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perp(- unit_dir.y, unit_dir.x);

    sf::Vector2f offset = ( thickness / 2.f ) * unit_perp;

    vertices[0].position = begin + offset;
    vertices[1].position = end + offset;
    vertices[2].position = end - offset;
    vertices[3].position = begin - offset;

    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;

    window->draw(vertices, 4, sf::Quads);
}*/