#ifndef KTASK_H
#define KTASK_H

#include <QObject>

class KTask : public QObject
{
    Q_OBJECT
public:
    explicit KTask(QObject *parent = 0);

signals:

public slots:
};

#endif // KTASK_H
