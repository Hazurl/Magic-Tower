#include "../../Header/GameState/Hex.h"

Hex::Hex(int x, int y, Hex::Type type) : x(x), y(y), type(type) {
    
}

Hex::~Hex() {
    
}

int Hex::getX() const {
    return x;
} 

int Hex::getY() const {
    return y;
} 

Hex::Type Hex::getType() const {
    return type;
}

std::string Hex::to_string(Hex::Type type) {
    switch(type) {
        case Hex::Type::Ground:
            return "Ground";
        case Hex::Type::Lava:
            return "Lava";
        case Hex::Type::Wall:
            return "Wall";
        default:
            return "undefined";
    }
}