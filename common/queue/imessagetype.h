#ifndef IMESSAGETYPE_H
#define IMESSAGETYPE_H

#include <QObject>

class IMessageType : public QObject {
    Q_OBJECT
public:
    explicit IMessageType(QObject *parent = 0);

signals:

public slots:
};

#endif // IMESSAGETYPE_H
