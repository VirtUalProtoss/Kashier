#include <QCoreApplication>

#include "service.h"


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Service service(8765);
    service.initComponents();
    service.prepareSubcribes();

    return app.exec();
}
