#include "tcpserver.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    TCPServer server(8765);

    app.exec();
}
