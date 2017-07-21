#ifndef __HEX
#define __HEX
#include "../Utilities/DebugMacro.h"

class Hex {
    GIVE_ACCESS_DEBUG()

public:
    Hex(int x = 0, int y = 0);
    ~Hex();

    int getX() const;
    int getY() const;

    bool isOnSameLine(const Hex* hex) const;

private:
    int x, y;
};

#endif