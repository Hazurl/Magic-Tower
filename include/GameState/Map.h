#ifndef __MAP
#define __MAP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cassert>
#include <functional>
#include <unordered_set>
#include <cstdlib>
#include <algorithm>

#include <GameObject/HexGO.h>
#include <Utilities/RessourcesLoader.h>
#include <Utilities/DebugMacro.h>

class Map {
    GIVE_ACCESS_DEBUG()

public:
    Map(unsigned int size);
    ~Map();

    const Hex* getHexAt(int x, int y) const;
    Hex* getHexAt(int x, int y);

    std::vector<const Hex*> filterHexes (std::function<bool(const Hex*)> pred) const;
    std::vector<const HexGO*> getHexes() const;
    std::vector<const Hex*> getNeighboursOf(const Hex* hex) const;
    std::vector<Hex*> getNeighboursOf(const Hex* hex);
    std::vector<const Hex*> getNeighboursWalkablesOf(const Hex* hex) const;

    int hexDistance(const Hex* hex0, const Hex* hex1) const;
    bool hexOnSameLine(const Hex* hex0, const Hex* hex1) const;

    void generateRandom();
    void generatePropagation();

private:
    
    int hexDistance(int x0, int y0, int x1, int y1) const;
    long hashCoords(int x, int y) const;

    unsigned int size;
    
    std::map<long, HexGO> hexes = {};
};

#endif