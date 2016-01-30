#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include "onyma.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Onyma *logicOnyma = new Onyma();
    logicOnyma->connectDB();
    w.setOnyma(logicOnyma);


    return a.exec();
    logicOnyma->disconnectDB();
}
