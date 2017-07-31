#ifndef __REACHABLE_HEXES
#define __REACHABLE_HEXES

#include <GameState/GameState.h>
#include <map>

class ReachableHexes {
public:
    static std::map<const Hex*, int> find(const Map& map, const Hex* start, int distance);

private:
    static void find_helper (Map const& map, std::map<const Hex*, int>& already, const Hex* center, int distance);
};

#endif