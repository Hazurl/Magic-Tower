#ifndef __HEX
#define __HEX

#include <string>
#include <iostream>
#include <cmath>

#include <Utilities/RessourcesLoader.h>
#include <Utilities/SceneManager.h>
#include <Components/Renderer/Renderer.h>

#include <frameworkHaz/2DGOInclude.hpp>

class Hex : public haz::Component {
public:
    struct Comparator {
        bool operator() (Hex const& h0, Hex const& h1) const {
            return h0.x == h1.x && h0.y == h1.y;
        }
    };
    struct ComparatorPtr {
        bool operator() (const Hex* h0, const Hex* h1) const {
            return h0->x == h1->x && h0->y == h1->y;
        }
    };
    enum class Type {
        Ground, Lava, Wall,

        Unknown,
        Size
    };

    Hex(haz::GameObject* go);
    Hex(haz::GameObject* go, int x, int y, Type type = Type::Ground);
    ~Hex();

    std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
        
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    Type getType() const;
    void setType(Type type);

    haz::Component* clone(haz::GameObject* go) const;

    static std::string to_string (Type type);
    static bool walkable(const Hex* hex);

    friend bool operator==(Hex const& lhs, Hex const& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator!=(Hex const& lhs, Hex const& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<< (std::ostream& os, Hex const& hex);

private:
    int x, y;

    Type type;

    Renderer* rend = nullptr;

    void updateTexture();
    void updatePosition();
};

namespace std {

    template <>
    struct hash<Hex> {
        std::size_t operator()(const Hex& k) const {
            return ( hash<int>()(k.getX())     )
                 ^ ( hash<int>()(k.getY()) << 1);
        }
    };

    template <>
    struct hash<Hex*> {
        std::size_t operator()(const Hex*& k) const {
            return ( hash<int>()(k->getX())     )
                 ^ ( hash<int>()(k->getY()) << 1);
        }
    };

}

#endif