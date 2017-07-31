#ifndef __COLLIDER
#define __COLLIDER

#include <SFML/Graphics.hpp>
#include <GameState/Camera.h>

class Collider {
public:
    Collider();
    virtual ~Collider();

    virtual bool isColliding(float x, float y) = 0;
    virtual void draw(sf::RenderWindow& window, Camera const& camera) = 0;
private:

};

#endif