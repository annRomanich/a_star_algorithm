#ifndef ASTARALGO_H
#define ASTARALGO_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct Coord{
    int x, y;
};

ostream& operator<<(ostream& os, const Coord& coord);
bool operator<(const Coord& l, const Coord& r);
bool operator==(const Coord& l, const Coord& r);
double distance(Coord start, Coord end);

struct Visited{
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

bool operator<(const Visited& l, const Visited& r);

// Класс для представления графа
class Graph {
    vector<vector<int>> field;

public:
    Graph(vector<vector<int>> f)
        : field(f)
    {
    }

    // Функция для обхода графа в ширину
    vector<Coord> BFS(Coord start, Coord goal) {
        auto startNode = make_shared<Visited>(start);
        startNode->estimate = distance(start, goal);

        set<shared_ptr<Visited>> openSet{
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
//            cout << current << " ";

            // Получаем все смежные вершины текущей вершины и если они не были посещены,
            // помечаем их как посещенные и добавляем в очередь
            for (auto neighbour : neighbours(current->coord)) {
                if (closedSet.count(neighbour) || field[neighbour.y][neighbour.x] == 1) {
                    continue;
                }
                double newLen = current->pathLength + 1;
                auto neighbourNode = openSet.find(make_shared<Visited>(neighbour));
                if (neighbourNode != openSet.end()) {
                     if(newLen < (*neighbourNode)->pathLength) {
                        (*neighbourNode)->parent = current;
                        (*neighbourNode)->pathLength = newLen;
                        (*neighbourNode)->estimate = distance((*neighbourNode)->coord, goal);
                    }
                }
                else {
                    auto newNeighbourNode = make_shared<Visited>(neighbour);
                    newNeighbourNode->parent = current;
                    newNeighbourNode->pathLength = newLen;
                    newNeighbourNode->estimate = distance(newNeighbourNode->coord, goal);
                    openSet.insert(newNeighbourNode);
                }
            }
        }

        return {};
    }

    vector<Coord> neighbours(Coord c)
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
               neighbour.x < field.at(0).size() && neighbour.y < field.size()) {
                result.push_back(neighbour);
            }
        }

        return result;
    }
};

#endif // ASTARALGO_H
