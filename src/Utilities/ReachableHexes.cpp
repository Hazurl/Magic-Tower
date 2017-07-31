#include <Utilities/ReachableHexes.h>

std::map<const Hex*, int> ReachableHexes::find (Map const& map, const Hex* start, int distance) {
    std::map<const Hex*, int> hexes = {};
    find_helper(map, hexes, start, distance);

    return hexes;
}

void ReachableHexes::find_helper (Map const& map, std::map<const Hex*, int>& already, const Hex* center, int distance) {
    if (distance <= 0)
        return;

    for (auto n : map.getNeighboursWalkablesOf(center)) {
        if (already.find(n) == already.end() || already[n] < distance) {
            already[n] = distance;
            find_helper(map, already, n, distance - 1);
        }
    }
}