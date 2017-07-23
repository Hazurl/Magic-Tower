#ifndef __MAP
#define __MAP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <cstdlib>

#include "../GameObject/HexGO.h"
#include "../Utilities/RessourcesLoader.h"
#include "../Utilities/DebugMacro.h"

class Map {
    GIVE_ACCESS_DEBUG()

public:
    Map(unsigned int size);
    ~Map();

    const Hex* getHexAt(int x, int y) const;

    std::vector<const Hex*> filterHexs (std::function<bool(const Hex*)> pred) const;
    std::vector<const HexGO*> getHexes() const;

    int hexDistance(const Hex* hex0, const Hex* hex1) const;
    bool hexOnSameLine(const Hex* hex0, const Hex* hex1) const;


private:
    
    int hexDistance(int x0, int y0, int x1, int y1) const;
    long hashCoords(int x, int y) const;

    unsigned int size;
    
    std::map<long, HexGO> hexes = {};
};

#endif