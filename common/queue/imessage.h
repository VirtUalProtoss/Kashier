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
    IMessage(QString msg);
    static IMessage fromStream(QByteArray* message);
    virtual QString getName();
    virtual void setType(IMessageType* type);
    virtual void setBody(IMessageBody* body);
    virtual void setSender(QString sender);
    virtual void setTarget(QString target);
    virtual void setText(QString text);
    virtual void setHash(QString hash);
    virtual bool needResponce() { return false; }
    virtual QString getHash();
    virtual QString getText();
    virtual QString getType();
    virtual QString getSender();
    virtual QString getTarget();

    virtual QString toString();
    virtual void fromString(QString msg);
signals:

public slots:

private:
    QString m_sender;
    QString m_target;
    QString m_hash;
    IMessageType* m_type;
    IMessageBody* m_body;
    QString m_text;
};

#endif // IMESSAGE_H
