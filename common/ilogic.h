#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>

#include "imessage.h"

class QueueBroker;

class ILogic : public QObject {
    Q_OBJECT

public:
    explicit ILogic(QObject *parent = 0);

    virtual void setInitParams(QMap<QString, QVariant>* initParams);
    virtual QString getName();
    virtual void setName(QString name);
    virtual bool isPublic();
    virtual void receive(IMessage*);
    virtual void run();
    QString getType() { return QString("Logic"); }

signals:
    void message(QString);
    void message(IMessage*);
    void init_complete();

public slots:
    void emit_message(IMessage*);

protected:
    QString name = "ILogic";
    QMap<QString, QVariant>* _initParams;
    QueueBroker* m_broker;
};

#endif // ILOGIC_H
