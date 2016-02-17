#ifndef IMESSAGEBODY_H
#define IMESSAGEBODY_H

#include <QObject>

class IMessageBody : public QObject {
    Q_OBJECT
public:
    explicit IMessageBody(QObject *parent = 0);

signals:

public slots:
};

#endif // IMESSAGEBODY_H
