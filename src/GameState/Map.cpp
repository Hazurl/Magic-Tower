/*#include <GameState/Map.h>

Map::Map(unsigned int size) : size(size) {
    generatePropagation();
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

Hex* Map::getHexAt(int x, int y) {
    long hash = hashCoords(x, y);
    if (hexes.find(hash) == hexes.end())
        return nullptr;
    return &hexes.at(hash);
}

long Map::hashCoords(int x, int y) const {
    return (static_cast<long>(x) << 32) + y;
}

std::vector<const Hex*> Map::filterHexes (std::function<bool(const Hex*)> pred) const {
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

std::vector<const Hex*> Map::getNeighboursOf(const Hex* hex) const {
    int x = hex->getX();
    int y = hex->getY();
    
    auto it_NW = hexes.find(hashCoords(x, y - 1));
    auto it_SE = hexes.find(hashCoords(x, y + 1));
    auto it_NE = hexes.find(hashCoords(x + 1, y - 1));
    auto it_SW = hexes.find(hashCoords(x - 1, y + 1));
    auto it_W = hexes.find(hashCoords(x - 1, y));
    auto it_E = hexes.find(hashCoords(x + 1, y));

    std::vector<const Hex*> neighbours = {};
    if (it_NW != hexes.end()) neighbours.push_back(&it_NW->second);
    if (it_SE != hexes.end()) neighbours.push_back(&it_SE->second);
    if (it_NE != hexes.end()) neighbours.push_back(&it_NE->second);
    if (it_SW != hexes.end()) neighbours.push_back(&it_SW->second);
    if (it_W != hexes.end()) neighbours.push_back(&it_W->second);
    if (it_E != hexes.end()) neighbours.push_back(&it_E->second);

    return std::move(neighbours);
}

std::vector<Hex*> Map::getNeighboursOf(const Hex* hex) {
    int x = hex->getX();
    int y = hex->getY();
    
    auto it_NW = hexes.find(hashCoords(x, y - 1));
    auto it_SE = hexes.find(hashCoords(x, y + 1));
    auto it_NE = hexes.find(hashCoords(x + 1, y - 1));
    auto it_SW = hexes.find(hashCoords(x - 1, y + 1));
    auto it_W = hexes.find(hashCoords(x - 1, y));
    auto it_E = hexes.find(hashCoords(x + 1, y));

    std::vector<Hex*> neighbours = {};
    if (it_NW != hexes.end()) neighbours.push_back(&it_NW->second);
    if (it_SE != hexes.end()) neighbours.push_back(&it_SE->second);
    if (it_NE != hexes.end()) neighbours.push_back(&it_NE->second);
    if (it_SW != hexes.end()) neighbours.push_back(&it_SW->second);
    if (it_W != hexes.end()) neighbours.push_back(&it_W->second);
    if (it_E != hexes.end()) neighbours.push_back(&it_E->second);

    return std::move(neighbours);
}

std::vector<const Hex*> Map::getNeighboursWalkablesOf(const Hex* hex) const {
    int x = hex->getX();
    int y = hex->getY();
    
    auto it_NW = hexes.find(hashCoords(x, y - 1));
    auto it_SE = hexes.find(hashCoords(x, y + 1));
    auto it_NE = hexes.find(hashCoords(x + 1, y - 1));
    auto it_SW = hexes.find(hashCoords(x - 1, y + 1));
    auto it_W = hexes.find(hashCoords(x - 1, y));
    auto it_E = hexes.find(hashCoords(x + 1, y));

    std::vector<const Hex*> neighbours = {};
    if (it_NW != hexes.end() && Hex::walkable(&it_NW->second)) neighbours.push_back(&it_NW->second);
    if (it_SE != hexes.end() && Hex::walkable(&it_SE->second)) neighbours.push_back(&it_SE->second);
    if (it_NE != hexes.end() && Hex::walkable(&it_NE->second)) neighbours.push_back(&it_NE->second);
    if (it_SW != hexes.end() && Hex::walkable(&it_SW->second)) neighbours.push_back(&it_SW->second);
    if (it_W != hexes.end() && Hex::walkable(&it_W->second)) neighbours.push_back(&it_W->second);
    if (it_E != hexes.end() && Hex::walkable(&it_E->second)) neighbours.push_back(&it_E->second);

    return std::move(neighbours);
}

void Map::generateRandom() {
    int radius = size;
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

void Map::generatePropagation() {
    int hex_start_x = static_cast<int>(rand() % std::min(size, (unsigned int)4));
    int hex_start_y = static_cast<int>(rand() % std::min(size, (unsigned int)4));

    int radius = size;
    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius; y <= radius; ++y) {
            if (hexDistance(x, y, 0, 0) >= radius)
                continue;

            HexGO hex(x, y, Hex::Type::Unknown);
            hexes.emplace( hashCoords(x, y), hex );
        }
    }

    std::vector<Hex*> to_build { getHexAt(hex_start_x, hex_start_y) };
    unsigned int pos = 0;

    while(pos < to_build.size()) {
        Hex* cur = to_build[pos];
        // set cur Type
        int distance = hexDistance(hex_start_x, hex_start_y, cur->getX(), cur->getY());
        double ratio = distance / static_cast<double>(size);
        int rand_type = rand() % 100;

            Ground -> 90% to 50%
            Wall -> 10% to 20%
            Lava -> 0% to 30%

        int prob_ground = (90 - static_cast<int>(ratio * 40.0));
        int prob_wall = prob_ground + (10 + static_cast<int>(ratio * 10.0));

        if (rand_type < prob_ground)
            cur->setType(Hex::Type::Ground);
        else if (rand_type < prob_wall)
            cur->setType(Hex::Type::Wall);
        else
            cur->setType(Hex::Type::Lava);

        // Add Neighbours at the end
        for (auto* n : getNeighboursOf(cur))
            if (n->getType() == Hex::Type::Unknown)
                to_build.push_back(n);

        // Advance Cur
        ++pos;
    }
}*/