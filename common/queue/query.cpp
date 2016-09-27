#include "query.h"
#include "QCryptographicHash"

Query::Query() {

}

Query::Query(IMessage *message) : IMessage(message) {
    processParams(message->getText());
}

void Query::processParams(QString params) {
    QStringList items = params.split("::");
    m_command = items[0];
    //QString result = QString("");
    if (items.length() > 1) {
        QStringList pList = items[1].split(";");
        foreach (QString param, pList) {
            if (param.length() == 0)
                continue;
            QStringList pArr = param.split("==");
            QString key = pArr[0];
            QString value = QString("");
            if (pArr.length() > 1)
                value = pArr[1];
            m_params[key] = value;
        }
    }
}

Query::Query(IMessage &message) {
    processParams(message.getText());
}

Query::Query(QString command, QMap<QString, QVariant> &params) {

}

QString Query::getHash() {
    if (m_params.count() > 0) {
        QString hash;

        foreach (QVariant param, m_params.values()) {
            hash += param.toString();
        }
        QString blah = QString(QCryptographicHash::hash(hash.toUtf8(), QCryptographicHash::Md5).toHex());
        return blah;
    }
    else
        return QString("=HASH=");
}
