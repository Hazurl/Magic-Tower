#include "../Header/Hex.h"

Hex::Hex(int x, int y) : x(x), y(y) {

}

Hex::~Hex() {
    
}

int Hex::getX() const {
    return x;
} 

int Hex::getY() const {
    return y;
} 

bool Hex::isOnSameLine (const Hex* hex) const {
    return hex->x == x || hex->y == y || -(hex->x - x) == (hex->y - y);
}