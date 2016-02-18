#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>

#include "imessagebody.h"
#include "imessagetype.h"
#include "imessagesender.h"


class IMessage : public QObject {
    Q_OBJECT
public:
    explicit IMessage(QObject *parent = 0);
    static IMessage fromStream(QByteArray* message);
    QString getName();
signals:

public slots:

private:
    IMessageSender* sender;
    IMessageType* type;
    IMessageBody body;
};

#endif // IMESSAGE_H
