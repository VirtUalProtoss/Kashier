#ifndef TEST_BROKER_H
#define TEST_BROKER_H

#include <QObject>

class Test_Broker : public QObject {
    Q_OBJECT
public:
    explicit Test_Broker(QObject *parent = 0);

signals:

public slots:
private slots:
    void search();
    void search_data();

};

#endif // TEST_BROKER_H
