#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include "kashiercommon_global.h"

class QueueBroker;

class KASHIERCOMMONSHARED_EXPORT Service : public QObject {
    Q_OBJECT
public:
    explicit Service(QObject *parent = 0);

    void loadPlugins();
signals:

private:
    QueueBroker* broker;
};

#endif // SERVICE_H
