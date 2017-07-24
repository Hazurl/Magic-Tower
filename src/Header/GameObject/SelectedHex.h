#ifndef __SELECTEDHEXGO
#define __SELECTEDHEXGO

#include <SFML/Graphics.hpp>

#include "../Interface/Animate.h"
#include "../GameState/Hex.h"
#include "../Utilities/DebugMacro.h"

class SelectedHex : public Animate {
    GIVE_ACCESS_DEBUG()
public:
    SelectedHex(const Hex* hex);
    ~SelectedHex();

    const Hex* getHex() const;
    sf::Color getColor() const;

private:
    const Hex* hex;

    // Animation
    bool color_up = true;
};

#endif