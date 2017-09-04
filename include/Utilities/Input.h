#ifndef __INPUT
#define __INPUT

#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Utilities/DebugMacro.h>

#include <frameworkHaz/Geometry/2D/Vector.hpp>

#define X_BUTTON(X)\
    X(MouseLeft, sf::Mouse::isButtonPressed(sf::Mouse::Left), "Mouse Left")\
    X(MouseRight, sf::Mouse::isButtonPressed(sf::Mouse::Right), "Mouse Right")\
    X(Space, sf::Keyboard::isKeyPressed(sf::Keyboard::Space), "Space")\
    X(Escape, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape), "Escape")\
    X(Action_1, sf::Keyboard::isKeyPressed(sf::Keyboard::Num1), "Action 1")\
    X(Action_2, sf::Keyboard::isKeyPressed(sf::Keyboard::Num2), "Action 2")\
    X(Action_3, sf::Keyboard::isKeyPressed(sf::Keyboard::Num3), "Action 3")\
    X(Up, sf::Keyboard::isKeyPressed(sf::Keyboard::Z), "Up")\
    X(Down, sf::Keyboard::isKeyPressed(sf::Keyboard::S), "Down")\
    X(Left, sf::Keyboard::isKeyPressed(sf::Keyboard::Q), "Left")\
    X(Right, sf::Keyboard::isKeyPressed(sf::Keyboard::D), "Right")

#define X_AXIS(X)\
X(Vertical, Down, Up)\
X(Horizontal, Left, Right)

class Input {
    GIVE_ACCESS_DEBUG()

public:
    enum class Button {
#define X(a, b, c) a,
        X_BUTTON(X)
#undef X
    };

    enum class Axis {
#define X(a, b, c) a,
        X_AXIS(X)
#undef X
    };

    enum class ButtonState {
        Pressed,
        Released,
        Up,
        Down
    };
    
    static float getMouseX();
    static float getMouseY();
    static haz::_2D::Vectorf getMousePosition();
    static bool isPressed(Button but);
    static bool isReleased(Button but);
    static bool isUp(Button but);
    static bool isDown(Button but);
    static float getScroll();

    static int getAxis(Axis axis);

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