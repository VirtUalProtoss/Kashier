//#include <QCoreApplication>

#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "test_subscribe.h"

int main(int argc, char *argv[]) {

    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Test_Subscribe, argc, argv);
    return 0;


    //QCoreApplication a(argc, argv);

    //return a.exec();
}
