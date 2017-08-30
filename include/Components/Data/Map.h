#ifndef __MAP
#define __MAP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <functional>
#include <unordered_set>
#include <cstdlib>
#include <algorithm>

#include <Utilities/RessourcesLoader.h>
#include <Utilities/PrefabFactory.h>
#include <Components/Data/Hex.h>

#include <frameworkHaz/2DGOInclude.hpp>

class Map : public haz::Component {
public:
    Map(haz::GameObject* go);
    ~Map();

    std::string to_string() const;
    
    haz::Component* clone(haz::GameObject* go) const;

    const Hex* getHexAt(int x, int y) const;
    Hex* getHexAt(int x, int y);

    std::vector<const Hex*> filterHexes (std::function<bool(const Hex*)> pred) const;
    std::vector<const Hex*> getHexes() const;
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

    const unsigned int size = 8;
    
    std::map<long, Hex*> hexes = {};
};

#endif