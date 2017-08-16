#include <Components/Renderer/HexRenderer.h>

float HexRenderer::HEIGHT_HEX_PIXELS = 50;
float HexRenderer::WIDTH_HEX_PIXELS = HexRenderer::HEIGHT_HEX_PIXELS * sqrt(3) / 2;

HexRenderer::HexRenderer(haz::GameObject* go) : Component(go) {

}

HexRenderer::~HexRenderer() {
    
}

void HexRenderer::draw (sf::RenderWindow& window, Camera const& camera) {
    if (hex == nullptr) {
        hex = getGO()->getComponent<Hex>();
        if (hex == nullptr)
            hex = getGO()->addComponent<Hex>(0, 0, Hex::Type::Lava);
    }

    if (last_type != hex->getType())
        updateSpriteTexture(window, camera);

    else if (last_x != hex->getX() || last_y != hex->getY())
        updateSpritePosition(window, camera);

    window.draw(sp);

    last_type = hex->getType();
    last_x = hex->getX();
    last_y = hex->getY();
}

haz::Component* HexRenderer::clone(haz::GameObject* go) const {
    return new HexRenderer(go);
}

void HexRenderer::onEnable() {
    enable();
}

void HexRenderer::onDisable() {
    disable();
}

const sf::Texture& HexRenderer::getTexture(Hex::Type type) {
    if (type == Hex::Type::Ground)
        return *TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_ground");
    else if (type == Hex::Type::Lava)
        return *TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_lava");
    else if (type == Hex::Type::Wall)
        return *TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_wall");

    HAZ_ASSERT(false);
}

void HexRenderer::updateSpritePosition(sf::RenderWindow& window, Camera const& camera) {
    auto screenSize = window.getSize();
    sp.setPosition( 
          sf::Vector2f ( (hex->getX() + (hex->getY() / 2.f)) * HexRenderer::WIDTH_HEX_PIXELS  * camera.getZoom(),  (hex->getY() * 0.75f) * HexRenderer::HEIGHT_HEX_PIXELS * camera.getZoom() )
        + sf::Vector2f ( screenSize.x / 2.f + camera.getPositionX(), screenSize.y / 2.f + camera.getPositionY() )
    );
}

void HexRenderer::updateSpriteTexture(sf::RenderWindow& window, Camera const& camera) {
    sp.setTexture(getTexture(hex->getType()));
    auto rect = sp.getTextureRect();

    float scale = (50 * camera.getZoom()) / static_cast<float>(rect.height);
    sp.setScale(scale, scale);
    sp.setOrigin(rect.width / 2, rect.height / 2);

    updateSpritePosition(window, camera);
}