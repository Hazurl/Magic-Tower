#include <Utilities/Input.h>

float Input::mouseX = 0;
float Input::mouseY = 0;
float Input::scroll = 0;

std::map<Input::Button, Input::ButtonState> Input::inputs {
    { Input::Button::MouseLeft, Input::ButtonState::Up },
    { Input::Button::MouseRight, Input::ButtonState::Up },
    { Input::Button::Space, Input::ButtonState::Up },
    { Input::Button::Escape, Input::ButtonState::Up },
    { Input::Button::Action_1, Input::ButtonState::Up },
    { Input::Button::Action_2, Input::ButtonState::Up },
    { Input::Button::Action_3, Input::ButtonState::Up },
};

float Input::getMouseX() {
    return Input::mouseX;
}

float Input::getMouseY() {
    return Input::mouseY;
}

sf::Vector2f Input::getMousePosition() {
    return { Input::mouseX, Input::mouseY };
}

bool Input::isPressed(Input::Button but)  {
    assert(Input::inputs.find(but) != Input::inputs.end());

    return Input::inputs.at(but) == Input::ButtonState::Pressed;
}

bool Input::isReleased(Input::Button but) {
    assert(Input::inputs.find(but) != Input::inputs.end());

    return Input::inputs.at(but) == Input::ButtonState::Released;
}

bool Input::isUp(Input::Button but) {
    assert(Input::inputs.find(but) != Input::inputs.end());

    auto st = Input::inputs.at(but);
    
    return st == Input::ButtonState::Released || st == Input::ButtonState::Up;
}

bool Input::isDown(Input::Button but) {
    assert(Input::inputs.find(but) != Input::inputs.end());

    auto st = Input::inputs.at(but);
    
    return st == Input::ButtonState::Pressed || st == Input::ButtonState::Down;
}

float Input::getScroll() {
    return Input::scroll;
}

Input::ButtonState Input::getButtonState(Input::Button but) {
    assert(Input::inputs.find(but) != Input::inputs.end());

    return Input::inputs.at(but);
}

void Input::resetEvents() {
    Input::scroll = 0;
}

void Input::updateButtonsStates(sf::RenderWindow& window) {
    // Buton::MouseLeft
    Input::changeState(Input::Button::MouseLeft, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    // Buton::MouseRight
    Input::changeState(Input::Button::MouseRight, sf::Mouse::isButtonPressed(sf::Mouse::Right));
    // Buton::Space
    Input::changeState(Input::Button::Space, sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    // Buton::Escape
    Input::changeState(Input::Button::Escape, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    // Buton::Action_1
    Input::changeState(Input::Button::Action_1, sf::Keyboard::isKeyPressed(sf::Keyboard::Num1));
    // Buton::Action_2
    Input::changeState(Input::Button::Action_2, sf::Keyboard::isKeyPressed(sf::Keyboard::Num2));
    // Buton::Action_3
    Input::changeState(Input::Button::Action_3, sf::Keyboard::isKeyPressed(sf::Keyboard::Num3));

    auto posMouse = sf::Mouse::getPosition(window);
    Input::mouseX = posMouse.x; 
    Input::mouseY = posMouse.y; 
}

void Input::onScrollEvent(float scrollDelta) {
    Input::scroll += scrollDelta;
}

void Input::changeState(Button but, bool is_pressed) {
    assert(inputs.find(but) != inputs.end());

    switch (Input::inputs[but]) {
        case Input::ButtonState::Down:
        case Input::ButtonState::Pressed:
            if (is_pressed)
                Input::inputs[but] = Input::ButtonState::Down;
            else
                Input::inputs[but] = Input::ButtonState::Released;
            break;

        case Input::ButtonState::Up:
        case Input::ButtonState::Released:
            if (is_pressed)
                Input::inputs[but] = Input::ButtonState::Pressed;
            else
                Input::inputs[but] = Input::ButtonState::Up;
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
            assert(false && ("Button not implemented : " + static_cast<int>(but)));
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
            assert(false && ("Button state not implemented : " + static_cast<int>(but_state)));
    }
}
