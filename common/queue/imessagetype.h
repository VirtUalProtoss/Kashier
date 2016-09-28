#ifndef IMESSAGETYPE_H
#define IMESSAGETYPE_H

#include <QString>

class IMessageType {
public:
    explicit IMessageType(QString type = "Message");

    QString toString();
    void fromString(QString type);

private:
    QString m_type = "Message";
};

#endif // IMESSAGETYPE_H
