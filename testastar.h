#ifndef TESTASTAR_H
#define TESTASTAR_H

#include <QTest>
#include "astaralgo.h"

class TestAStar : public QObject
{
    Q_OBJECT
private slots:
    void happyPath() {
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
        auto a = g.BFS(start, end);
        vector<Coord> expected{{2,4}, {1,4}, {0,3}, {1,2}, {2,1}, {3,0}, {4,1}, {4,2}, {4,3}, {4,4}};

        QCOMPARE(a, expected);
    }
};

#endif // TESTASTAR_H
