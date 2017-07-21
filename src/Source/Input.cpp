#include "../Header/Input.h"

Input::Input() : inputs({
        { Input::Button::MouseLeft, Input::ButtonState::Up },
        { Input::Button::MouseRight, Input::ButtonState::Up },
        { Input::Button::Space, Input::ButtonState::Up },
        { Input::Button::Escape, Input::ButtonState::Up },
        { Input::Button::Action_1, Input::ButtonState::Up },
        { Input::Button::Action_2, Input::ButtonState::Up },
        { Input::Button::Action_3, Input::ButtonState::Up },
    }) {
    updateButtonsStates();
}

Input::~Input() {

}

bool Input::isPressed(Input::Button but) const  {
    assert(inputs.find(but) != inputs.end());

    return inputs.at(but) == Input::ButtonState::Pressed;
}

bool Input::isRealeased(Input::Button but) const {
    assert(inputs.find(but) != inputs.end());

    return inputs.at(but) == Input::ButtonState::Released;
}

bool Input::isUp(Input::Button but) const {
    assert(inputs.find(but) != inputs.end());

    auto st = inputs.at(but);
    
    return st == Input::ButtonState::Released || st == Input::ButtonState::Up;
}

bool Input::isDown(Input::Button but) const {
    assert(inputs.find(but) != inputs.end());

    auto st = inputs.at(but);
    
    return st == Input::ButtonState::Pressed || st == Input::ButtonState::Down;
}

Input::ButtonState Input::getButtonState(Input::Button but) const {
    assert(inputs.find(but) != inputs.end());

    return inputs.at(but);
}

void Input::updateButtonsStates() {
    // Buton::MouseLeft
    changeState(Input::Button::MouseLeft, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    // Buton::MouseRight
    changeState(Input::Button::MouseRight, sf::Mouse::isButtonPressed(sf::Mouse::Right));
    // Buton::Space
    changeState(Input::Button::Space, sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    // Buton::Escape
    changeState(Input::Button::Escape, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    // Buton::Action_1
    changeState(Input::Button::Action_1, sf::Keyboard::isKeyPressed(sf::Keyboard::Num1));
    // Buton::Action_2
    changeState(Input::Button::Action_2, sf::Keyboard::isKeyPressed(sf::Keyboard::Num2));
    // Buton::Action_3
    changeState(Input::Button::Action_3, sf::Keyboard::isKeyPressed(sf::Keyboard::Num3));
}

void Input::changeState(Button but, bool is_pressed) {
    assert(inputs.find(but) != inputs.end());

    switch (inputs[but]) {
        case Input::ButtonState::Down:
        case Input::ButtonState::Pressed:
            if (is_pressed)
                inputs[but] = Input::ButtonState::Up;
            else
                inputs[but] = Input::ButtonState::Released;
            break;

        case Input::ButtonState::Up:
        case Input::ButtonState::Released:
            if (is_pressed)
                inputs[but] = Input::ButtonState::Pressed;
            else
                inputs[but] = Input::ButtonState::Down;
            break;
    }
}

std::string Input::to_string(Input::Button but) {
    switch(but) {
        case Input::Button::MouseLeft :
            return "Mouse Left";
        case Input::Button::MouseRight :
            return "Mouse Right";
        case Input::Button::Space :
            return "Space";
        case Input::Button::Escape :
            return "Escape";
        case Input::Button::Action_1 :
            return "Action 1";
        case Input::Button::Action_2 :
            return "Action 2";
        case Input::Button::Action_3 :
            return "Action 3";
        default :
            assert(("Button not implemented : " + static_cast<int>(but), false));
    }
}

std::string Input::to_string(Input::ButtonState but_state) {
    switch(but_state) {
        case Input::ButtonState::Pressed :
            return "Pressed";
        case Input::ButtonState::Released :
            return "Released";
        case Input::ButtonState::Down :
            return "Down";
        case Input::ButtonState::Up :
            return "Up";
        default :
            assert(("Button state not implemented : " + static_cast<int>(but_state), false));
    }
}
