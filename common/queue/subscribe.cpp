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
        m_source = URI(coms[0]);
        m_destination = URI(coms[1]);
        m_type = coms[2];
        m_wait_type = coms[3];
    }
    else if (coms.length() == 3) {
        m_source = URI(coms[0]);
        m_destination = URI(coms[1]);
        m_type = coms[2];
        m_wait_type = "Temp";
    }
    else {
        qDebug() << "Invalid subscribe" << sub;
        qDebug() << "Format: source;destination;message_type;wait_type";
    }
}

Subscribe::Subscribe(const Subscribe& sub) {
    m_subscribe = sub.m_subscribe;
    m_addTime = QDateTime::currentDateTime();
    m_source = URI(sub.m_source);
    m_destination = URI(sub.m_destination);
    m_type = sub.m_type;
    m_wait_type = sub.m_wait_type;
}

QString Subscribe::getHash() {
    QString hash = m_subscribe;
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

bool Subscribe::addrMatch(URI destination) {

    QString srcComponent = m_source.getComponent();
    QString dstComponent = destination.getComponent();

    if (srcComponent == dstComponent)
        return true;

    QString nSrcComp = URI::normalizeComponentName(srcComponent);
    QString nDstComp = URI::normalizeComponentName(dstComponent);

    if (nSrcComp == nDstComp)
         return true;
}
