#ifndef __HEX_COLLIDER
#define __HEX_COLLIDER

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include <Collider/Collider.h>
#include <GameState/Hex.h>

class HexCollider : public Collider {
public:
    HexCollider(const Hex* hex, float x, float y, float size);
    ~HexCollider();

    bool isColliding(float x, float y);
    void draw (sf::RenderWindow& window);

    const Hex* const hex;

private:
    float x, y, height, width;

    static float WIDTH_HEX;
    
};

#endif