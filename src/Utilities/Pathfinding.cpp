#include <Utilities/Pathfinding.h>

PathFinding::PathFinding (const Map* map) : map(map) {
    assert(map != nullptr);
}

PathFinding::~PathFinding() {

}

bool PathFinding::getPath(const Hex* start, const Hex* end, std::vector<const Hex*>& result) const {
    result.clear();

    if (start == nullptr || end == nullptr)
        return false;

    if (*start == *end) {
        return true;
    }

    std::set<const Hex*> closed = {};
    std::map<const Hex*, PathFinding::Weight> open = {};

    std::map<const Hex*, const Hex*> parent = {};

    open.insert({ start, {map->hexDistance(start, end), 0}});

    while (!open.empty()) {
        auto pair = std::min_element(open.begin(), open.end(), [] (const std::pair<const Hex*, Weight>& p0, const std::pair<const Hex*, Weight>& p1) -> bool  {
            return p0.second.heuristic + p0.second.cost < p1.second.heuristic + p1.second.cost;
        });

        const Hex* cur = pair->first;
        PathFinding::Weight weight = pair->second;
        open.erase(pair);

        closed.insert(cur);

        if (*cur == *end) {
            const Hex* current = end;

            do {
                result.push_back(current);
                current = parent[current];
            } while (*current != *start);

            result.push_back(start);
            std::reverse(result.begin(), result.end());

            return true;
        }

        for (const Hex* neighbour : map->getNeighboursWalkablesOf(cur)) {
            if (closed.find(neighbour) != closed.end())
                continue;

            auto it_open = open.find(neighbour);
            int new_cost = weight.cost + map->hexDistance(cur, neighbour);

            if (it_open == open.end() || new_cost < it_open->second.cost) {
                PathFinding::Weight new_weight = { map->hexDistance(neighbour, end), new_cost };

                if (it_open != open.end())
                    open.erase(it_open);

                open.insert({neighbour, new_weight});

                parent[neighbour] = cur;
            }
        }
    }

    return false;
}


