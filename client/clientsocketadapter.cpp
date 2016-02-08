#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>

ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {
    // TODO: replace this to set params from config (ini file)
    m_ptcpSocket->connectToHost("127.0.0.1", 8765);
}
