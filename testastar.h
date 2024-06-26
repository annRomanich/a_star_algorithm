#ifndef TESTASTAR_H
#define TESTASTAR_H

#include <QTest>
#include "astaralgo.h"

class TestAStar : public QObject
{
    Q_OBJECT
private slots:
    void happyPath() {
        vector<vector<int>> field ({
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
        });
        Coord start{2, 4};
        Coord end{4, 4};
        auto actual = aStarSearch(start, end, field);

        vector<Coord> expected{{2,4}, {1,4}, {0,3}, {1,2}, {2,1}, {3,0}, {4,1}, {4,2}, {4,3}, {4,4}};


        QCOMPARE(actual, expected);
    }
};

#endif // TESTASTAR_H
