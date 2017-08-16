#include <Components/Data/Hex.h>

Hex::Hex(haz::GameObject* go) : Hex(go, 0, 0, Hex::Type::Unknown) {
    
}

Hex::Hex(haz::GameObject* go, int x, int y, Hex::Type type) : haz::Component(go), x(x), y(y), type(type) {
    
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

void Hex::setType(Hex::Type type) {
    this->type = type;
}

haz::Component* Hex::clone(haz::GameObject* go) const {
    return new Hex(go, x, y, type);
}

std::string Hex::to_string(Hex::Type type) {
    switch(type) {
        case Hex::Type::Ground:
            return "Ground";
        case Hex::Type::Lava:
            return "Lava";
        case Hex::Type::Wall:
            return "Wall";
        case Hex::Type::Unknown:
            return "Unknown";
        default:
            return "undefined";
    }
}

bool Hex::walkable(const Hex* hex) {
    return hex != nullptr && hex->getType() == Hex::Type::Ground;
}

std::ostream& operator<< (std::ostream& os, Hex const& hex) {
    os << "(" << hex.x << ", " << hex.y << ")";
    return os;
}
