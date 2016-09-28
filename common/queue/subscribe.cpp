#include "subscribe.h"
#include <QStringList>
#include <QDebug>
#include "uri.h"
#include <QCryptographicHash>

Subscribe::Subscribe() {

}

Subscribe::Subscribe(QString sub) {
    m_subscribe = sub;
    m_addTime = QDateTime::currentDateTime();
    QStringList coms = m_subscribe.split(";");
    if (coms.length() == 4) {
        m_source_transport = URI::getTransport(coms[0]);
        m_source_component = URI::getComponent(coms[0]);
        m_destination_transport = URI::getTransport(coms[1]);
        m_destination_component = URI::getComponent(coms[1]);
        m_type = URI::getComponent(coms[2]);
        m_wait_type = coms[3];
    }
    else if (coms.length() == 3) {
        m_source_transport = URI::getTransport(coms[0]);
        m_source_component = URI::getComponent(coms[0]);
        m_destination_transport = URI::getTransport(coms[1]);
        m_destination_component = URI::getComponent(coms[1]);
        m_type = URI::getComponent(coms[2]);
        m_wait_type = "Temp";
    }
    else {
        qDebug() << "Invalid subscribe" << sub;
        qDebug() << "Format: source;destination;message_type;wait_type";
    }
}

QString Subscribe::getHash() {
    QString hash = m_subscribe; //m_destination + ";" + m_source + ";" + m_type + ";" + m_wait_type;
    QString blah = QString(QCryptographicHash::hash(hash.toUtf8(), QCryptographicHash::Md5).toHex());
    return blah;
}

bool Subscribe::isTimeout() {
    if (m_wait_type == "Persist") {
        return false;
    }
    else {
        if (m_removeTime > QDateTime::currentDateTime())
            return true;
        else
            return false;
    }
}

bool Subscribe::addrMatch(QString source, QString destination) {
    if (source == "*")
        return true;

    QString srcComponent = URI::getComponent(source);
    QString dstComponent = URI::getComponent(destination);

    if (srcComponent == dstComponent)
        return true;

    QString nSrcComp = URI::normalizeComponentName(srcComponent);
    QString nDstComp = URI::normalizeComponentName(URI::getName(dstComponent));

    if (nSrcComp == nDstComp)
         return true;
}
