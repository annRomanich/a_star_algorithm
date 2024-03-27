#include <QCoreApplication>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct Coord{
    int x, y;
};

ostream& operator<<(ostream& os, const Coord& coord)
{
    os << "(" << coord.x << "," << coord.y << ")";
    return os;
}

bool operator<(const Coord& l, const Coord& r)
{
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

bool operator==(const Coord& l, const Coord& r)
{
    return l.x == r.x && l.y == r.y;
}

double distance(Coord start, Coord end) {
    double x = abs(end.x - start.x);
    double y = abs(end.y - start.y);
    return sqrt(pow(x, 2) + pow(y, 2));
}

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

bool operator<(const Visited& l, const Visited& r)
{
    return l.coord < r.coord;
}

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


//#include <QTest>

////class TestAStar : public QObject
////{
////    Q_OBJECT
////private slots:
////    void happyPath() {
////        // Создаем граф с 4 вершинами
////        Graph g({
////                    {0, 0, 0, 0, 0},
////                    {0, 0, 0, 1, 0},
////                    {0, 0, 0, 1, 0},
////                    {0, 1, 1, 1, 0},
////                    {0, 0, 0, 1, 0},
////                });
////        Coord start{2, 4};
////        Coord end{4, 4};
////        auto a = g.BFS(start, end);
////        vector<Coord> expected{{2,4}, {1,4}, {0,3}, {1,2}, {2,1}, {3,0}, {4,1}, {4,2}, {4,3}};

////        QCOMPARE(a, expected);
////    }
////};

////int main () {
////    QTest::qExec(new TestAStar);
////    return 0;
////}


int main() {

    // Создаем граф с 4 вершинами
    Graph g({
                {0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 1, 0},
                {0, 1, 1, 1, 0},
                {0, 0, 0, 1, 0},
            });

    Coord start{2, 4};
    Coord end{4, 4};
    cout << "Breadth First Traversal started from vertex " << start << " to " << end << ": " ;
    auto a = g.BFS(start, end);
    for(auto i : a) {
        cout << i;
    }

    return 0;
}

