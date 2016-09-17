#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>

#include "imessage.h"


class ILogic : public QObject {
    Q_OBJECT

public:
    explicit ILogic(QObject *parent = 0);

    virtual QString getName();
    virtual void setName(QString name);
    virtual bool isPublic();
    virtual void receive(IMessage*);
    virtual void run();

signals:
    void message(QString);
    void message(IMessage*);

public slots:
    void emit_message(IMessage*);

private:
    QString name = "ILogic";
};

#endif // ILOGIC_H
