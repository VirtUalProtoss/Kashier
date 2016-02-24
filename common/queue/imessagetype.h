#ifndef IMESSAGETYPE_H
#define IMESSAGETYPE_H

#include <QObject>

class IMessageType : public QObject {
    Q_OBJECT
public:
    explicit IMessageType(QObject *parent = 0, QString type = "Message");

    QString toString();
signals:

public slots:

private:
    QString m_type;
};

#endif // IMESSAGETYPE_H
