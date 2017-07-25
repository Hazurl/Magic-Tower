#include <Collider/HexCollider.h>

float HexCollider::WIDTH_HEX = sqrt(3) / 2;

HexCollider::HexCollider(const Hex* hex, float x, float y, float size) : Collider(), hex(hex), x(x), y(y), height(size / 2), width(HexCollider::WIDTH_HEX * size) {
    //std::cout << "HexCollider : " << x << ", " << y << ", " << size << std::endl;
}

HexCollider::~HexCollider() {

}

bool HexCollider::isColliding(float x, float y) {
    float q2x = std::abs(x - this->x);
    float q2y = std::abs(y - this->y);
    if (q2y > width || q2x > height * 2) 
        return false;
    return (2 * height * width - height * q2x - width * q2y) >= 0;
}

void HexCollider::draw(sf::RenderWindow& window) {
    sf::CircleShape bounds(height * 2, 6);
    bounds.setFillColor(sf::Color::Transparent);
    bounds.setPosition(x - height * 2, y - height * 2);
    bounds.setOutlineColor(sf::Color::Green);
    bounds.setOutlineThickness(3);
    window.draw(bounds);
}