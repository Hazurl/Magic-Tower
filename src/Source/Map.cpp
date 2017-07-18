#include "../Header/Map.h"

float Map::WIDTH_HEX = sqrt(3) / 2;

Map::Map(unsigned int size) : size(size), hex_sprite(*RessourcesLoader::load<sf::Texture>("hex_sprite", "image/Hex.png")) {
    hex_sprite.setColor(sf::Color(200, 200, 200));
    float scale = HEX_HEIGHT_PIXEL / static_cast<float>(hex_sprite.getTextureRect().height);
    hex_sprite.setScale(scale, scale);

    int radius = size - 1;
    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius; y <= radius; ++y) {
            if (hexDistance(x, y, 0, 0) >= radius)
                continue;
            Hex hex(x, y);
            hexs[hashCoords(x, y)] = hex;
        }
    }
}

Map::~Map() {

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

sf::Vector2f Map::relativePosition(int x, int y) {
    return { Map::WIDTH_HEX * (x + y / 2.f), y * 0.75f };
}

void Map::draw(sf::RenderWindow& window) {
    int width = window.getSize().x;
    int height = window.getSize().y;

    auto rect = hex_sprite.getGlobalBounds();
    sf::Vector2f origin { width / 2.f - rect.width / 2.f, height / 2.f - rect.height / 2.f };


    for (auto& p : hexs) {
        Hex& hex = p.second;
        auto rel_pos = relativePosition(hex.getX(), hex.getY());
        hex_sprite.setPosition( rel_pos.x * rect.width + origin.x, rel_pos.y * rect.height + origin.y );
        if (highlightedHex.find(hashCoords(hex.getX(), hex.getY())) != highlightedHex.end())
            hex_sprite.setColor(sf::Color::Green);
        else
            hex_sprite.setColor(sf::Color(200, 200, 200));

        window.draw(hex_sprite);
    }

}

const Hex* Map::getHexAt(int x, int y) const {
    long hash = hashCoords(x, y);
    if (hexs.find(hash) == hexs.end())
        return nullptr;
    return &hexs.at(hash);
}


long Map::hashCoords(int x, int y) const {
    return (static_cast<long>(x) << 32) + y;
}

std::vector<const Hex*> Map::filterHexs (std::function<bool(const Hex*)> pred) const {
    std::vector<const Hex*> filteredHex = {};
    for (auto& p : hexs) {
        if (pred(&p.second))
            filteredHex.push_back(&p.second);
    }
    return std::move(filteredHex);
}

void Map::highlightHex(const Hex* hex) {
    long hash = hashCoords(hex->getX(), hex->getY());
    highlightedHex.insert(hash);
}
