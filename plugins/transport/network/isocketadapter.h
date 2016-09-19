#ifndef ISOCKETADAPTER_H
# define ISOCKETADAPTER_H

# include <QObject>
#include "itransport.h"


class ISocketAdapter : public QObject {
    Q_OBJECT
public:
    explicit ISocketAdapter(QObject *parent);
    virtual ~ISocketAdapter();
    virtual void sendString(const QString& str) = 0;
    virtual bool isConnected();

signals:
    void message(QString text);
    void disconnected();
};

#endif // ISOCKETADAPTER_H
