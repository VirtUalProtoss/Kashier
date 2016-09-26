#include "socketadapter.h"

#include <QVector>
#include <QTcpSocket>
#include <QDataStream>

SocketAdapter::SocketAdapter(QObject *parent, QTcpSocket *pSock) : QObject(parent), m_msgSize(-1) {
    m_ptcpSocket->IPv4Protocol;
    if (0 == pSock)
        m_ptcpSocket = new QTcpSocket(this);
    else
        m_ptcpSocket = pSock;
    name = QString("");
    connect(m_ptcpSocket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    connect(m_ptcpSocket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(m_ptcpSocket, SIGNAL(connected()), this, SLOT(on_connected()));
}

SocketAdapter::~SocketAdapter() {

}

void SocketAdapter::on_message(ITransport *tr, IMessage *msg) {
    emit sock_message(tr, msg);
}

void SocketAdapter::on_readyRead() {
    QString buff;
    QDataStream stream(m_ptcpSocket);

    while(true) {
        if (m_msgSize < 0) {
            if (m_ptcpSocket->bytesAvailable() < sizeof(int))
                return;
            stream >> m_msgSize;
        }
        else {
            if (m_ptcpSocket->bytesAvailable() < m_msgSize)
                return;
            stream >> buff;
            emit message(buff);
            m_msgSize = -1;
        }
    }
}

QString SocketAdapter::getName() {
    if (name.length() == 0)
        return m_ptcpSocket->objectName();
    else
        return name;
}

void SocketAdapter::setName(QString pName) {
    name = pName;
}

void SocketAdapter::sendString(const QString& str) {
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);

    sendStream << quint16(0) << str;

    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));

    m_ptcpSocket->write(block);
}

void SocketAdapter::on_send(QString msg) {
    sendString(msg);
}

void SocketAdapter::on_disconnected() {
    m_ptcpSocket->deleteLater();
    m_connected = false;
    emit disconnected();
}

void SocketAdapter::on_connected() {
    m_connected = true;
    emit connected();
}

void SocketAdapter::disconnect() {
    m_connected = false;
}

void SocketAdapter::sock_connect(QString host, int port) {
    m_ptcpSocket->connectToHost(host, port);
    if (m_ptcpSocket->waitForConnected(1000)) {
         //setName(QString("Network<" + getAddress() + QString(">")));
        emit connected();
    }
}
