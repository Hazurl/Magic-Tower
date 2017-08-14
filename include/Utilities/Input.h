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
        MouseLeft,
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
    
    static float getMouseX();
    static float getMouseY();
    static sf::Vector2f getMousePosition();
    static bool isPressed(Button but);
    static bool isReleased(Button but);
    static bool isUp(Button but);
    static bool isDown(Button but);
    static float getScroll();

    static ButtonState getButtonState(Button but);

    static void resetEvents();
    static void updateButtonsStates(sf::RenderWindow& window);
    static void onScrollEvent(float scrollDelta);

    static std::string to_string(Button but);
    static std::string to_string(ButtonState but_state);

private:
    static void changeState(Button but, bool is_pressed);

    static std::map<Button, ButtonState> inputs;
    static float mouseX, mouseY;
    static float scroll;
};

#endif