#include "test_subscribe.h"
#include "queue/subscribe.h"

#include <QDebug>
#include <QTest>
#include <QString>


Test_Subscribe::Test_Subscribe(QObject *parent) : QObject(parent) {

}

void Test_Subscribe::subscribe() {
    QFETCH(QString, subStr);
    Subscribe sub_1 = Subscribe(subStr);
    QFETCH(bool, tOut);
    QCOMPARE(sub_1.toString(), subStr);
    QCOMPARE(sub_1.isTimeout(), tOut);
}

void Test_Subscribe::subscribe_data() {
    QTest::addColumn<QString>("subStr");
    QTest::addColumn<bool>("tOut");

    QTest::newRow("subscribe_data_1") << "*;Broker;Message;Persist" << false;
    QTest::newRow("subscribe_data_1") << "*;Broker;Message;Temp" << true;
}
