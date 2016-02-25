#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QObject>

class Subscribe : public QObject {
    Q_OBJECT
public:
    explicit Subscribe(QObject *parent = 0);

signals:

public slots:
};

#endif // SUBSCRIBE_H
