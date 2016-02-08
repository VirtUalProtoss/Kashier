#ifndef KKM_H
#define KKM_H

#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QString>
#include <QDebug>

QT_USE_NAMESPACE

#define ENQ 0x05
#define ACK 0x06
#define NAK 0x15
#define STX 0x02

struct command {
    int code;
    QString name;
    int timeout;
};

struct errorCode {
    int code;
    QString name;
};

class KKM : public QObject {
    Q_OBJECT
public:
    explicit KKM(QObject *parent = 0);
    int openSerialPort();
    bool initConnection(int retryCount);
    void beep();

private:
    bool ready = false;
    QSerialPort *serialPort = new QSerialPort(this);

    QString serialPortName = "/dev/ttyUSB0";
    int serialPortBaudRate = 115200;

    QByteArray int2char(int value, int length, int base);
    QByteArray read(int timeout);
    void getMessageBytes(int code, QByteArray &message, QByteArray &msgBytes);
    bool execCommand(int code, QMap<QString, QVariant> &params);

signals:

public slots:
};

#endif // KKM_H
