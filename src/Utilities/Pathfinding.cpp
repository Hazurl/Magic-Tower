#include <Utilities/Pathfinding.h>

PathFinding::PathFinding (const Map* map) : map(map) {
    assert(map != nullptr);
}

PathFinding::~PathFinding() {

}

PathFinding::Cell PathFinding::hexToCell(const Hex* hex) const {
    assert(hex == nullptr);
    return PathFinding::Cell(hex->getX(), hex->getY());
}

const Hex* PathFinding::cellToHex(PathFinding::PathFinding::Cell const& cell) const {
    return map->getHexAt(cell.x, cell.y);
}

std::vector<PathFinding::PathFinding::Cell> PathFinding::getNeighbours(PathFinding::PathFinding::Cell const& cell) const {
    std::vector<PathFinding::Cell> neighbours = {};

    for(const Hex* hex : map->getNeighboursOf(cellToHex(cell)))
        neighbours.emplace_back(hex->getX(), hex->getY());

    return std::move(neighbours);
}


bool PathFinding::getPath(const Hex* start, const Hex* end, std::vector<const Hex*>& result) const {
    result.clear();

    if (start == nullptr || end == nullptr)
        return false;

    const PathFinding::Cell startCell (start->getX(), start->getY());
    const PathFinding::Cell endCell (end->getX(), end->getY());

    std::vector<PathFinding::Cell> closed_list = {};
    std::set<PathFinding::Cell, CellsComparator> open_list = {};

    open_list.insert(startCell);

    while (!open_list.empty()) {
        PathFinding::Cell current = *open_list.begin();
        open_list.erase(open_list.begin());

        if (current == endCell) {
            for (PathFinding::Cell& c : closed_list)
                result.push_back(cellToHex(c));

            return true;
        }
        for (PathFinding::Cell& n : getNeighbours(current)) {
            auto it_closed = std::find(closed_list.begin(), closed_list.end(), n);
            auto it_open = std::find(open_list.begin(), open_list.end(), n);

            if ((it_closed == closed_list.end() || it_closed->cost >= current.cost) && (it_open == open_list.end() || it_open->cost >= current.cost)) {
                n.cost = current.cost + 1;
                n.heuristic = n.cost + map->hexDistance(cellToHex(n), end);
                open_list.insert(n);
            }
        }
        closed_list.push_back(current);
    }
    return false;
}


