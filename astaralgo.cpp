#include "astaralgo.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <set>
#include <cmath>

struct Visited {
    Coord coord;
    shared_ptr<Visited> parent;

    double pathLength = 0;
    double estimate = 0;

    Visited(Coord c, shared_ptr<Visited> p = nullptr)
        : coord(c), parent(p)
    {
    }

    double fValue() {
        return pathLength + estimate;
    }
    vector<Coord> reconstructPath() {
        vector<Coord> currentPath;

        auto current = this;
        while (current != nullptr) {
            currentPath.insert(currentPath.begin(), current->coord);
            current = current->parent.get();
        }

        return currentPath;
    }
};
ostream& operator<<(ostream& os, const Coord& coord) {
    os << "(" << coord.x << "," << coord.y << ")";
    return os;
}

bool operator<(const Coord& l, const Coord& r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

bool operator==(const Coord& l, const Coord& r) {
    return l.x == r.x && l.y == r.y;
}

double distance(Coord start, Coord end) {
    double x = abs(end.x - start.x);
    double y = abs(end.y - start.y);
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool operator<(const Visited& l, const Visited& r) {
    return l.coord < r.coord;
}

vector<Coord> neighbours(Coord c, vector<vector<int>> field)
{
    vector<Coord> result;
    for (Coord neighbour : vector<Coord>{
            {c.x - 1, c.y},
            {c.x - 1, c.y - 1},
            {c.x    , c.y - 1},
            {c.x + 1, c.y - 1},
            {c.x + 1, c.y},
            {c.x + 1, c.y + 1},
            {c.x    , c.y + 1},
            {c.x - 1, c.y + 1},
        })
    {
        if(neighbour.x >= 0 && neighbour.y >= 0 &&
           neighbour.x < int(field.at(0).size()) && neighbour.y < int(field.size())) {
            result.push_back(neighbour);
        }
    }

    return result;
}

vector<Coord> aStarSearch(Coord start, Coord goal, vector<vector<int>> field) {
    auto startNode = make_shared<Visited>(start);
    startNode->estimate = distance(start, goal);

    vector<shared_ptr<Visited>> openSet{
        startNode,
    };
    set<Coord> closedSet;

    while (!openSet.empty()) {
        auto currentIt = std::min_element(openSet.begin(), openSet.end(), [](auto& l, auto& r){
            return l->fValue() < r->fValue();
        });
        if (currentIt == openSet.end()) {
            throw std::logic_error("openSet is empty");
        }

        auto current = *currentIt;

        if (current->coord == goal) {
            return current->reconstructPath();
        }

        openSet.erase(currentIt);
        closedSet.insert(current->coord);

        for (auto neighbour : neighbours(current->coord, field)) {
            if (closedSet.count(neighbour) || field[neighbour.y][neighbour.x] == 1) {
                continue;
            }

            auto neighbourNodeIt = std::find_if(openSet.begin(), openSet.end(),
                                              [&](auto& i){return i->coord == neighbour;});

            shared_ptr<Visited> neighbourNode;
            if (neighbourNodeIt != openSet.end()) {
                neighbourNode = *neighbourNodeIt;
            }
            else {
                neighbourNode = openSet.emplace_back(make_shared<Visited>(neighbour));
                neighbourNode->pathLength = std::numeric_limits<double>::infinity();
            }

            double newLen = current->pathLength + 1;
            if (newLen < neighbourNode->pathLength) {
                neighbourNode->parent = current;
                neighbourNode->pathLength = newLen;
                neighbourNode->estimate = distance(neighbourNode->coord, goal);
            }
        }
    }
    return {};
}
