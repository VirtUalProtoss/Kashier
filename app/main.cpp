#include <QCoreApplication>

#include "service.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "Load common lib";
    Service* service = new Service();
    qDebug() << "Finish loading common lib";

    return app.exec();
}
