#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>


class ILogic : public QObject {
    Q_OBJECT
public:
    explicit ILogic(QObject *parent);

signals:

public slots:
};

#endif // ILOGIC_H
