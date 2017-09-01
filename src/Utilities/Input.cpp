#include <Utilities/Input.h>

float Input::mouseX = 0;
float Input::mouseY = 0;
float Input::scroll = 0;

std::map<Input::Button, Input::ButtonState> Input::inputs {
#define X(a, b, c) { Input::Button::a, Input::ButtonState::Up },
    X_BUTTON(X)
#undef X
};

float Input::getMouseX() {
    return Input::mouseX;
}

float Input::getMouseY() {
    return Input::mouseY;
}

haz::_2D::Vectorf Input::getMousePosition() {
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
#define X(a, b, c) Input::changeState(Input::Button::a, b);
    X_BUTTON(X)
#undef X

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
#define X(a, b, c) case Input::Button::a : return c;
        X_BUTTON(X)
#undef X
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
