#ifndef SOCKETADAPTER_H
# define SOCKETADAPTER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class ITransport;
class IMessage;

class SocketAdapter : public QObject {
    Q_OBJECT
public:
      SocketAdapter(QObject *parent, QTcpSocket *pSock = 0);
      ~SocketAdapter();
      void sendString(const QString& str);
      QString getName();
      void setName(QString);
      inline bool isConnected() { return m_connected; }
      void sock_connect(QString host, int port);

      inline QString getAddress() { return m_ptcpSocket->peerAddress().toString(); }
      inline int getPort() { return m_ptcpSocket->peerPort(); }

      inline QString getLocalAddress() { return m_ptcpSocket->localAddress().toString(); }
      inline int getLocalPort() { return m_ptcpSocket->localPort(); }

      inline QString getRemoteAddress() { return m_ptcpSocket->peerAddress().toString(); }
      inline int getRemotePort() { return m_ptcpSocket->peerPort(); }

public slots:
      void on_send(QString);
      void disconnect();
protected slots:
      void on_readyRead();
      void on_disconnected();
      void on_connected();
      void on_message(ITransport*, IMessage*);
protected:
      QTcpSocket *m_ptcpSocket;
      qint16 m_msgSize;
      QString name;
      bool m_connected;
signals:
    void sock_message(ITransport*, IMessage*);
    void message(QString text);
    void disconnected();
};

#endif // SOCKETADAPTER_H
