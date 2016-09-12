#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H

#include <QObject>
#include "imessage.h"
#include "imessagetype.h"
#include "imessagebody.h"
#include "query.h"


class MessageBuilder : public QObject {
    Q_OBJECT
public:
    explicit MessageBuilder(QObject *parent = 0);

    void setType(QString type);
    IMessage* getMessage(QString target, QString command, QMap<QString, QVariant> params);
    void setSender(QString sender);
    void setText(QString text);
signals:

public slots:

private:
    IMessage* message;
};

#endif // MESSAGEBUILDER_H
