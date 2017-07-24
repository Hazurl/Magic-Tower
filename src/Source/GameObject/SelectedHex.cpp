#include "../../Header/GameObject/SelectedHex.h"

SelectedHex::SelectedHex(const Hex* hex) : hex(hex) {
    createAnimation("color");
    setRepeated("color", true, 2000);
    createEvent("color", 0, [this] (float t, float) { std::cout << "TRUE : " << t << std::endl; this->color_up = true; });
    createEvent("color", 1000, [this] (float t, float) { std::cout << "FALSE : " << t << std::endl; this->color_up = false; });
}

SelectedHex::~SelectedHex() {

}

const Hex* SelectedHex::getHex() const {
    return hex;
}

sf::Color SelectedHex::getColor() const {
    if (color_up)
        return sf::Color(255, 0, 0, getProgress("color") * 255);
    else
        return sf::Color(255, 0, 0, 255 - getProgress("color") * 255);
}