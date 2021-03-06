#ifndef __INPUT
#define __INPUT

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#include <Utilities/DebugMacro.h>

class Input {
    GIVE_ACCESS_DEBUG()

public:
    enum class Button {
        MouseLeft = 42,
        MouseRight,
        Space,
        Escape,
        Action_1,
        Action_2,
        Action_3
    };

    enum class ButtonState {
        Pressed,
        Released,
        Up,
        Down
    };
    
    Input();
    ~Input();

    float getMouseX() const;
    float getMouseY() const;
    sf::Vector2f getMousePosition() const;
    bool isPressed(Button but) const;
    bool isReleased(Button but) const;
    bool isUp(Button but) const;
    bool isDown(Button but) const;
    float getScroll() const;

    ButtonState getButtonState(Button but) const;

    void resetEvents();
    void updateButtonsStates(sf::RenderWindow& window);
    void onScrollEvent(float scrollDelta);

    static std::string to_string(Button but);
    static std::string to_string(ButtonState but_state);

private:
    void changeState(Button but, bool is_pressed);

    std::map<Button, ButtonState> inputs;
    float mouseX, mouseY;
    float scroll;
};

#endif