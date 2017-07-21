#include "../../Header/GameObject/HexGO.h"

float HexGO::WIDTH_HEX = sqrt(3) / 2;

HexGO::HexGO(Hex const& hex) : Drawable(), Animate(), hex(hex), sprite(*RessourcesLoader::load<sf::Texture>("hex_ground", "image/Ground.png")) {
    sprite.setColor(sf::Color(200, 200, 200));
    float scale = HEX_HEIGHT_PIXEL / static_cast<float>(sprite.getTextureRect().height);
    sprite.setScale(scale, scale);
}

HexGO::~HexGO() {

}

void HexGO::draw(sf::RenderWindow& window, sf::Vector2f offset) {
    sf::Vector2f rel_pos = { HexGO::WIDTH_HEX * (hex.getX() + hex.getY() / 2.f), hex.getY() * 0.75f };

    auto sprite_rect = sprite.getGlobalBounds();
    auto screen_size = window.getSize();

    sf::Vector2f origin { screen_size.x / 2.f - sprite_rect.width / 2.f + offset.x,
                          screen_size.y / 2.f - sprite_rect.height / 2.f + offset.y };


    sprite.setPosition( rel_pos.x * sprite_rect.width + origin.x, 
                        rel_pos.y * sprite_rect.height + origin.y );
    window.draw(sprite);
}
