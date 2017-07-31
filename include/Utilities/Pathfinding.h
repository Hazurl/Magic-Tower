#ifndef __PATHFINDING
#define __PATHFINDING

#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include <GameState/Map.h>

class PathFinding {
public:
    struct Cell {
        Cell(const Hex* hex) : hex(hex), cost(0), heuristic(0) {}
        Cell(Cell const& c) : hex(c.hex), cost(c.cost), heuristic(c.heuristic) {}
        const Hex* hex;
        int cost;
        int heuristic;
    };
    friend bool operator==(Cell const& lhs, Cell const& rhs) {
        return *lhs.hex == *rhs.hex;
    }

    struct CellsComparator {
        bool operator() (Cell const& c0, Cell const& c1) const {
            return c0.heuristic + c0.cost < c1.heuristic + c1.cost;
        }
    };

public:
    PathFinding(const Map* map);
    ~PathFinding();

    bool getPath(const Hex* start, const Hex* end, std::vector<const Hex*>& result) const;
    //bool getPath_debug(const Hex* start, const Hex* end, std::vector<const Hex*>& result, std::vector<Cell>& res_closed_list, std::set<Cell, CellsComparator>& res_open_list) const;

private:
    const Map* map = nullptr;
};
    /*
bool operator==(PathFinding::Cell const& lhs, PathFinding::Cell const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}*/

namespace std {

    template <>
    struct hash<PathFinding::Cell> {
        std::size_t operator()(const PathFinding::Cell& k) const {
            return hash<const Hex*>()(k.hex);
        }
    };

}
#endif