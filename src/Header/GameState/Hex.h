#ifndef __HEX
#define __HEX

#include <string>

#include "../Utilities/DebugMacro.h"

class Hex {
    GIVE_ACCESS_DEBUG()

public:
    enum class Type {
        Ground, Lava, Wall,

        Size
    };

    Hex(int x, int y, Type type = Type::Ground);
    ~Hex();

    int getX() const;
    int getY() const;

    Type getType() const;

    static std::string to_string (Type type);

private:
    const int x, y;

    Type type;
};

#endif