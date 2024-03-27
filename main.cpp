#include <QCoreApplication>
#include <iostream>
#include "testastar.h"

int main () {
    QTest::qExec(new TestAStar);
    return 0;
}

//#include "main.moc"

//int main() {

//    // Создаем граф с 4 вершинами
//    Graph g({
//                {0, 0, 0, 0, 0},
//                {0, 0, 0, 1, 0},
//                {0, 0, 0, 1, 0},
//                {0, 1, 1, 1, 0},
//                {0, 0, 0, 1, 0},
//            });

//    Coord start{2, 4};
//    Coord end{4, 4};
//    cout << "Breadth First Traversal started from vertex " << start << " to " << end << ": " ;
//    auto a = g.BFS(start, end);
//    for(auto i : a) {
//        cout << i;
//    }

//    return 0;
//}

