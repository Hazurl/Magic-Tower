#ifndef __MAP
#define __MAP

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_set>

#include "Hex.h"
#include "RessourcesLoader.h"
#include "DebugMacro.h"

#define HEX_HEIGHT_PIXEL 50

class Map {
    GIVE_ACCESS_DEBUG()

public:
    Map(unsigned int size);
    ~Map();

    void draw(sf::RenderWindow& window);

    const Hex* getHexAt(int x, int y) const;
    void highlightHex (const Hex* hex) const;

    std::vector<const Hex*> filterHexs (std::function<bool(const Hex*)> pred) const;

    int hexDistance(int x0, int y0, int x1, int y1) const;
    int hexDistance(const Hex* hex0, const Hex* hex1) const;

    void highlightHex (const Hex* hex);

private:

    sf::Vector2f relativePosition(int x, int y);

    long hashCoords(int x, int y) const;

    unsigned int size;
    
    sf::Sprite hex_sprite;
    std::map<long, Hex> hexs = {};
    std::unordered_set<long> highlightedHex = {};

    static float WIDTH_HEX;
};

#endif