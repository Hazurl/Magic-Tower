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
        result = {start};
        return true;
    }

    std::set<Cell, CellsComparator> open = {};
    std::set<const Hex*> closed = {};

    std::map<long, const Hex*> parent = {};

    Cell start_cell(start);
    start_cell.heuristic = map->hexDistance(start, end);

    std::cout << "Add to open list : " << *start << " (size : ";
    open.insert(start_cell);
    std::cout << open.size() << ")" << std::endl;

    if (open.find(start_cell) != open.end()) {
        std::cout << "FOUND !" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }

    start_cell.cost = 42;

    std::cout << open.begin()->cost << std::endl;

    if (open.find(start_cell) != open.end()) {
        std::cout << "FOUND !" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
/*
    while (!open.empty()) {
        Cell cur = *open.begin();
        std::cout << "Remove from open list : " << *cur.hex << " (size : ";
        open.erase(open.begin());
        std::cout << open.size() << ")" << std::endl;

        std::cout << "Visited : " << *cur.hex << std::endl;
        std::cout << "Add to closed list : " << *cur.hex << " (size : ";
        closed.insert(Hex::hash(*cur.hex));
        std::cout << closed.size() << ")" << std::endl;

        if (*cur.hex == *end) {
            const Hex* current = start;

            int pos = 0;

            do {
                result.push_back(start);
                pos++;
                current = parent[Hex::hash(*current)];
            } while (current != nullptr && *current != *end);

            if (current == nullptr) {
                std::cout << "# ERROR : " << pos << std::endl;
                return false;
            }

            result.push_back(end);

            return true;
        }

        for (const Hex* neighbour : map->getNeighboursWalkablesOf(cur.hex)) {
            std::cout << "\tneighbour : " << *neighbour << std::endl;
            if (closed.find(Hex::hash(*neighbour)) != closed.end()) {
                std::cout << "\tAlready visited and evaluated !" << std::endl;
                continue;
            }

            auto it_open = open.find(Cell(neighbour));
            int new_cost = cur.cost + map->hexDistance(cur.hex, neighbour);

            std::cout << "\t\tnew_cost : " << new_cost << std::endl;
            if (it_open == open.end())
                std::cout << "\t\tNot in open list" << std::endl;
            else
                std::cout << "\t\tPrevious cost : " << it_open->cost << std::endl;
            if (it_open == open.end() || new_cost < it_open->cost) {
                Cell cell(neighbour);
                cell.cost = new_cost;
                cell.heuristic = map->hexDistance(neighbour, end);
                std::cout << "\t\tCell : " << *neighbour << ", Cost : " << new_cost << ", Heuristic : " << cell.heuristic << std::endl;

                if (it_open != open.end())
                    open.erase(it_open);

                std::cout << "\t\tAdd to open list : " << *neighbour << " (size : ";
                open.insert(cell);
                std::cout << open.size() << ")" << std::endl;

                std::cout << "\t\tAdd Parent (" << Hex::hash(*neighbour) << " : " << *cur.hex << ")" << std::endl;
                parent[Hex::hash(*neighbour)] = cur.hex;
            }
        }
    }*/

    return false;
}


