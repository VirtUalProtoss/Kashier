#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QByteArray>
#include "kkm.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Onyma *logicOnyma = new Onyma();
    //logicOnyma->connectDB();
    //w.setOnyma(logicOnyma);
    
    //KKM *shtrih = new KKM();
    //shtrih->beep();

    return a.exec();
    //logicOnyma->disconnectDB();
}
