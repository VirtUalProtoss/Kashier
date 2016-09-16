#ifndef TRANSPORTLOCAL_H
#define TRANSPORTLOCAL_H

#include "itransport.h"

class TransportLocal : public ITransport {
public:
    explicit TransportLocal(QObject *parent);
    QString getName();
    QString getAddress();

signals:

public slots:
};

#endif // TRANSPORTLOCAL_H
