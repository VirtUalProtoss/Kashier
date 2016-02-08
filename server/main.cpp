#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Server server(8765);

    app.exec();
}
