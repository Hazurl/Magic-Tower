#ifndef __HEXGO
#define __HEXGO

#include <Interface/Animate.h>
#include <GameState/Hex.h>

class HexGO : public Animate, public Hex {
public:
    HexGO(int x, int y, Hex::Type type = Type::Ground);
    ~HexGO();

private:

};

#endif