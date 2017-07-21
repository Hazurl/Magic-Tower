#ifndef __INPUT
#define __INPUT

#include <SFML/Graphics.hpp>
#include <cassert>
#include "DebugMacro.h"

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
    
    Input();
    ~Input();

    bool isPressed(Button but) const;
    bool isRealeased(Button but) const;
    bool isUp(Button but) const;
    bool isDown(Button but) const;

    ButtonState getButtonState(Button but) const;

    void updateButtonsStates();

    static std::string to_string(Button but);
    static std::string to_string(ButtonState but_state);

private:
    void changeState(Button but, bool is_pressed);

    std::map<Button, ButtonState> inputs;

};

#endif