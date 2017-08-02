#ifndef __PATHFINDING
#define __PATHFINDING

#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include <GameState/Map.h>

class PathFinding {
private:
    struct Weight {
        int heuristic, cost;
    };
public:
    static bool find(Map const& map, const Hex* start, const Hex* end, std::vector<const Hex*>& result);
};

#endif