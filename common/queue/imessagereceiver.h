#ifndef IMESSAGERECEIVER_H
#define IMESSAGERECEIVER_H

#include <QObject>

class IMessageReceiver : public QObject {
    Q_OBJECT
public:
    explicit IMessageReceiver(QObject *parent = 0);

signals:

public slots:
    void on_receive(QString message);
};

#endif // IMESSAGERECEIVER_H
