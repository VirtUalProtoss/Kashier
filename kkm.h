#ifndef KKM_H
#define KKM_H

#include <QObject>
#include <QSerialPort>
#include <QTextStream>

QT_USE_NAMESPACE

class KKM : public QObject
{
    Q_OBJECT
public:
    explicit KKM(QObject *parent = 0);
    int openSerialPort();

private:
    QSerialPort *serialPort;

    QString serialPortName = "/dev/ttyUSB0";
    int serialPortBaudRate = 115200;

signals:

public slots:
};

#endif // KKM_H
