/*#include <Collider/HexCollider.h>

float HexCollider::WIDTH_FACTOR = sqrt(3) / 2;

HexCollider::HexCollider(const Hex* hex, float x, float y, float radius) : Collider(), hex(hex), x(x), y(y), radius(radius), half_height(radius / 2), width(radius * HexCollider::WIDTH_FACTOR) {}
HexCollider::HexCollider(const Hex* hex, sf::Vector2f const& pos, float radius) : HexCollider(hex, pos.x, pos.y, radius) {}

HexCollider::~HexCollider() {

}

bool HexCollider::isColliding(float x, float y) {
    float q2x = std::abs(x - this->x);
    float q2y = std::abs(y - this->y);
    if (q2y > width || q2x > half_height * 2) 
        return false;
    return (2 * half_height * width - half_height * q2x - width * q2y) >= 0;
}

void HexCollider::draw(sf::RenderWindow& window, Camera const& camera) {
    float thickness = 1 * camera.getZoom();
    sf::CircleShape hexa(radius, 6);
    hexa.setOrigin(radius, radius);

    hexa.setFillColor(sf::Color::Transparent);
    hexa.setOutlineColor(sf::Color::Green);
    hexa.setOutlineThickness(thickness);

    hexa.setPosition( x, y );
    window.draw(hexa);
}*/