#ifndef TEST_SUBSCRIBE_H
#define TEST_SUBSCRIBE_H

#include <QObject>

class Test_Subscribe : public QObject
{
    Q_OBJECT
public:
    explicit Test_Subscribe(QObject *parent = 0);

signals:

public slots:

private slots:
    void subscribe();
    void subscribe_data();
};

#endif // TEST_SUBSCRIBE_H
