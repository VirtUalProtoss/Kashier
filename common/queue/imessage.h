#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>
#include <QStringList>

#include "imessagebody.h"
#include "imessagetype.h"
#include "imessagesender.h"


class IMessage : public QObject {
    Q_OBJECT
public:
    explicit IMessage(QObject *parent = 0);
    static IMessage fromStream(QByteArray* message);
    QString getName();
    void setType(IMessageType* type);
    void setBody(IMessageBody* body);
    void setSender(QString sender);
    void setTarget(QString target);
    void setText(QString text);
    QString getText();
    QString getSender();
    QString getTarget();

    QString toString();
    void fromString(QString msg);
signals:

public slots:

private:
    QString m_sender;
    QString m_target;
    IMessageType* m_type;
    IMessageBody* m_body;
    QString m_text;
};

#endif // IMESSAGE_H
