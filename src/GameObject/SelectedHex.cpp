#include <GameObject/SelectedHex.h>

SelectedHex::SelectedHex(const Hex* hex) : hex(hex), colorAnim(Animation<ColorState>(ColorState::Appear)), rotateAnim(Animation<RotateState>(RotateState::Rotate)) {
    colorAnim.addState(ColorState::Visible);
    colorAnim.addTransitionsFrom(ColorState::Appear, {
        { ColorState::Visible, new Triggers::EventElapsedTimePassed(2000) }
    });

    rotateAnim.addTransitionsFrom(RotateState::Rotate, {
        { RotateState::Rotate, new Triggers::EventElapsedTimePassed(2000) } 
    });
}

SelectedHex::~SelectedHex() {

}

const Hex* SelectedHex::getHex() const {
    return hex;
}

sf::Color SelectedHex::getColor() const {
    if (colorAnim.getState() == ColorState::Appear) {
        int alpha = static_cast<int>(colorAnim.getProgress() * 255);
        assert(alpha >= 0 && alpha <= 255);

        return sf::Color(200, 0, 100, alpha);
    }
    return sf::Color(200, 0, 100, 255);
}

float SelectedHex::getRotation() const {
    return rotateAnim.getProgress() * 360;
}

void SelectedHex::updateAnimations(float deltaTime) {
    colorAnim.update(deltaTime);
    rotateAnim.update(deltaTime);
}
