#ifndef SOCKETADAPTER_H
# define SOCKETADAPTER_H

#include "isocketadapter.h"


class QTcpSocket;
class SocketAdapter : public ISocketAdapter {
    Q_OBJECT
public:
      SocketAdapter(QObject *parent, QTcpSocket *pSock = 0);
      virtual ~SocketAdapter();
      virtual void sendString(const QString& str);
      virtual QString getName();
      virtual void setName(QString);
      inline bool isConnected() { return m_connected; }
public slots:
      void on_send(QString);
      void disconnect();
protected slots:
      void on_readyRead();
      void on_disconnected();
      void on_connected();
protected:
      QTcpSocket *m_ptcpSocket;
      qint16 m_msgSize;
      QString name;
      bool m_connected;
};

#endif // SOCKETADAPTER_H
