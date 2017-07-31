#ifndef __HEX_COLLIDER
#define __HEX_COLLIDER

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include <Collider/Collider.h>
#include <GameState/Hex.h>

class HexCollider : public Collider {
public:
    HexCollider(const Hex* hex, float x, float y, float radius);
    HexCollider(const Hex* hex, sf::Vector2f const& pos, float radius);
    ~HexCollider();

    bool isColliding(float x, float y);
    void draw (sf::RenderWindow& window, Camera const& camera);

    const Hex* const hex;

private:
    float x, y; // position on screen in pixels
    float radius; // radius
    float half_height, width; // ...

    static float WIDTH_FACTOR;
   
};

#endif