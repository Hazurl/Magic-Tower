#ifndef __PATHFINDING
#define __PATHFINDING

#include <map>
#include <queue>
#include <algorithm>

#include <GameState/Map.h>

class PathFinding {
private:
    struct Cell {
        Cell(int x, int y) : x(x), y(y), cost(0), heuristic(0) {}
        int x, y;
        int cost;
        int heuristic;

    };
    friend bool operator==(Cell const& lhs, Cell const& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    struct CellsComparator {
        bool operator() (Cell const& c0, Cell const& c1) const {
            return c0.heuristic > c1.heuristic;
        }
    };

public:
    PathFinding(const Map* map);
    ~PathFinding();

    bool getPath(const Hex* start, const Hex* end, std::vector<const Hex*>& result) const;

private:
    Cell hexToCell (const Hex* hex) const;
    const Hex* cellToHex (Cell const& cell) const;

    std::vector<Cell> getNeighbours(Cell const& cell) const;

    const Map* map = nullptr;
};
    /*
bool operator==(PathFinding::Cell const& lhs, PathFinding::Cell const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}*/

#endif