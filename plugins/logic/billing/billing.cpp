#include "billing.h"
#include "query.h"
#include "reply.h"

Billing::Billing(QObject *parent) : ILogic(parent) {
    m_onyma = new Onyma();
    connect(this, SIGNAL(init_complete()), this, SLOT(on_init_complete()));
}

QString Billing::getName() {
    return QString("Billing");
}

void Billing::on_init_complete() {
    m_onyma->connectDB(_initParams);
}

void Billing::receive(IMessage *msg) {
    qDebug() << getName() << "receive message" << msg->toString();
    if (msg->getProtocol() == 0) {
        qDebug() << "Old version of message protocol, skip processing";
        return;
    }
    if (msg->getType() == "Query") {
        Query *qMsg = new Query(msg);
        QMap<QString, QVariant> params = qMsg->getParams();
        m_onyma->execCommand(qMsg->getCommand(), params);

        Reply *reply = new Reply(qMsg);
        emit message(reply);
    }
}
