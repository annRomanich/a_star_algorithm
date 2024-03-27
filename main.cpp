#include <QCoreApplication>
#include <iostream>
#include "testastar.h"

int main () {
    QTest::qExec(new TestAStar);
    return 0;
}


