#ifndef __HEXGO
#define __HEXGO

#define HEX_HEIGHT_PIXEL 50

#include <cmath>

#include "../Interface/Animate.h"
#include "../Interface/Drawable.h"
#include "../GameState/Hex.h"

class HexGO : public Drawable, public Animate {
public:
    HexGO(Hex const& hex);
    ~HexGO();

    void draw(sf::RenderWindow& window, sf::Vector2f offset);

private:
    static float WIDTH_HEX;

    Hex const& hex;

    sf::Sprite sprite;

};

#endif