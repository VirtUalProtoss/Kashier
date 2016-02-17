#ifndef IMESSAGESENDER_H
#define IMESSAGESENDER_H

#include <QObject>

class IMessageSender : public QObject
{
    Q_OBJECT
public:
    explicit IMessageSender(QObject *parent = 0);

signals:

public slots:
};

#endif // IMESSAGESENDER_H
