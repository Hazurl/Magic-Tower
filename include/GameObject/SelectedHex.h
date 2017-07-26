#ifndef __SELECTEDHEXGO
#define __SELECTEDHEXGO

#include <SFML/Graphics.hpp>
#include <cassert>

#include <Interface/Animator.h>
#include <GameState/Hex.h>
#include <Utilities/DebugMacro.h>


class SelectedHex : public Animator {
    GIVE_ACCESS_DEBUG()
    enum class ColorState {
        Appear = 0, Visible = 1
    };
    enum class RotateState {
        Rotate = 2
    };

public:
    SelectedHex(const Hex* hex);
    ~SelectedHex();

    const Hex* getHex() const;
    sf::Color getColor() const;
    float getRotation() const;

    void updateAnimations(float deltaTime);

private:
    const Hex* hex;

    Animation<ColorState> colorAnim;
    Animation<RotateState> rotateAnim;
};

#endif