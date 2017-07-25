#include <GameObject/SelectedHex.h>

SelectedHex::SelectedHex(const Hex* hex) : hex(hex), color_up(true) {
    createAnimation("color");
    setRepeated("color", true, 2000);
    setSpeed("color", 0.1);
    createEvent("color", 0, [this] (float, float, float) { this->color_up = false; });
    createEvent("color", 1000, [this] (float, float, float) { this->color_up = true; });

    createAnimation("rotation");
    setRepeated("rotation", true, 5000);
    createEvent("rotation", 0);
}

SelectedHex::~SelectedHex() {

}

const Hex* SelectedHex::getHex() const {
    return hex;
}

sf::Color SelectedHex::getColor() const {
    float progress = getProgress("color");
    int alpha = static_cast<int>(progress * 256);
    assert(alpha >= 0 && alpha <= 255);

    if (color_up)
        return sf::Color(200, 0, 100, alpha);
    else
        return sf::Color(200, 0, 100, 255 - alpha);
}

float SelectedHex::getRotation() const {
    return getProgress("rotation") * 360;
}