#ifndef __DRAWABLE
#define __DRAWABLE

#include "../Utilities/RessourcesLoader.h"
#include <SFML/Graphics.hpp>

class Drawable {
public:

    Drawable();
    virtual ~Drawable();

    virtual void draw(sf::RenderWindow& window, sf::Vector2f offset) = 0;

private:

};

#endif