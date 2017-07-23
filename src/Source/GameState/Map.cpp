#include "../../Header/GameState/Map.h"

Map::Map(unsigned int size) : size(size) {
    int radius = size - 1;
    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius; y <= radius; ++y) {
            if (hexDistance(x, y, 0, 0) >= radius)
                continue;
            
            int rand_type = rand() % 100;
            Hex::Type type;

            if (rand_type < 60)
                type = Hex::Type::Ground;
            else if (rand_type < 85)
                type = Hex::Type::Lava;
            else
                type = Hex::Type::Wall;

            HexGO hex(x, y, type);
            hexes.emplace( hashCoords(x, y), hex );
        }
    }
}

Map::~Map() {

}


bool Map::hexOnSameLine (const Hex* hex0, const Hex* hex1) const {
    return hex0->getX() == hex1->getX() || hex0->getY() == hex1->getY() || -(hex0->getX() - hex1->getX()) == (hex0->getY() - hex1->getY());
}

int Map::hexDistance(int x0, int y0, int x1, int y1) const {
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (dx == 0)
        return dy < 0 ? -dy : dy;
    if (dy == 0)
        return dx < 0 ? -dx : dx;

    if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) {
        if (dx < 0)
            dx = -dx;
        if (dy < 0)
            dy = -dy;
        return dx + dy;
    } else {
        if (dx < 0)
            dx = -dx;
        if (dy < 0)
            dy = -dy;
        return dx < dy ? dy : dx;
    }
}

int Map::hexDistance(const Hex* hex0, const Hex* hex1) const {
    return hexDistance(hex0->getX(), hex0->getY(), hex1->getX(), hex1->getY());
}

const Hex* Map::getHexAt(int x, int y) const {
    long hash = hashCoords(x, y);
    if (hexes.find(hash) == hexes.end())
        return nullptr;
    return &hexes.at(hash);
}


long Map::hashCoords(int x, int y) const {
    return (static_cast<long>(x) << 32) + y;
}

std::vector<const Hex*> Map::filterHexs (std::function<bool(const Hex*)> pred) const {
    std::vector<const Hex*> filteredHex = {};
    for (auto& p : hexes) {
        if (pred(&p.second))
            filteredHex.push_back(&p.second);
    }
    return std::move(filteredHex);
}

std::vector<const HexGO*> Map::getHexes() const {
    std::vector<const HexGO*> vec_hexes = {};
    for (auto& p : hexes)
        vec_hexes.push_back(&p.second);

    return std::move(vec_hexes);
}
