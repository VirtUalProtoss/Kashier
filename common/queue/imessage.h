#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>
#include <QStringList>

#include "imessagebody.h"
#include "imessagetype.h"
#include "imessagesender.h"

#include "uri.h"

class IMessage : public QObject {
    Q_OBJECT
public:
    explicit IMessage(QObject *parent = 0);
    IMessage(QString msg);
    static IMessage fromStream(QByteArray* message);
    virtual inline QString getName() { return m_name; }
    virtual void setType(IMessageType* type);
    virtual void setName(QString name) { m_name = name; }
    virtual void setBody(IMessageBody* body);
    virtual void setSender(URI sender);
    virtual void setTarget(URI target);
    virtual void setText(QString text);
    virtual void setHash(QString hash);
    virtual bool needResponce();
    virtual QString getHash();
    virtual QString getText();
    virtual QString getType();
    virtual URI getSender();
    virtual URI getTarget();
    virtual QString getSubscribe();

    virtual QString toString();
    virtual void fromString(QString msg);
    inline int getProtocol() { return m_protocol; }
    inline void setProtocol(int proto) { m_protocol = proto; }
signals:

public slots:

protected:
    URI m_sender;
    URI m_target;
    QString m_hash = QString("");
    IMessageType* m_type;
    IMessageBody* m_body;
    QString m_text = QString("");
    QString m_name = QString("IMessage");
    int m_protocol = 0;
};

#endif // IMESSAGE_H
