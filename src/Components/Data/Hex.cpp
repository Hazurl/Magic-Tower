#include <Components/Data/Hex.h>

Hex::Hex(haz::GameObject* go) : Hex(go, 0, 0, Hex::Type::Unknown) {
    
}

Hex::Hex(haz::GameObject* go, int x, int y, Hex::Type type) : haz::Component(go), x(x), y(y), type(type), rend(go->getComponent<Renderer>()) {
    updateTexture();
}

Hex::~Hex() {
    
}

std::string Hex::to_string() const {
    return "{ (" + std::to_string(x) + ", " + std::to_string(y) + ") of type " + Hex::to_string(type) + " }";
}

std::vector<std::string> Hex::pretty_strings() const {
    return {
        "Position : " + haz::_2D::Vectori{x, y}.to_string(),
        "Type : " + Hex::to_string(type)
    };
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
    updateTexture();
}

void Hex::setX(int x) {
    this->x = x;
}

void Hex::setY(int y) {
    this->y = y;
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

void Hex::updateTexture() {
    if (rend == nullptr) {
        rend = gameobject()->getComponent<Renderer>();
    }

    if (rend != nullptr) {
        if (type == Hex::Type::Ground)
            rend->changeTexture(*TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_ground"));
        else if (type == Hex::Type::Lava)
            rend->changeTexture(*TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_lava"));
        else if (type == Hex::Type::Wall)
            rend->changeTexture(*TextureLoader::get(SceneManager::getCurrentIDScene(), "hex_wall"));
        else {
            rend->changeTexture(*TextureLoader::getDefault());
        }
    }
}

void Hex::updatePosition() {
    static float HEIGHT_HEX_PIXELS = 50;
    static float WIDTH_HEX_PIXELS = HEIGHT_HEX_PIXELS * sqrt(3) / 2;
    
    transform()->position( 
          haz::_2D::Vectorf ( (x + (y / 2.f)) * WIDTH_HEX_PIXELS,  
                              (y * 0.75f) * HEIGHT_HEX_PIXELS)
    );
}