#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

class ITransport : public QObject {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);

signals:

public slots:
};

#endif // ITRANSPORT_H
