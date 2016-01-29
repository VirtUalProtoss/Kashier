#include "kkm.h"


KKM::KKM(QObject *parent) : QObject(parent)
{
    // Test!
    serialPort->setPortName(serialPortName);
    serialPort->setBaudRate(serialPortBaudRate);
}

int KKM::openSerialPort()
{
    QTextStream standardOutput(stdout);
    if (!serialPort->open(QIODevice::ReadWrite)) {
        standardOutput << QObject::trUtf8("Не могу открыть порт %1, ошибка %2").arg(serialPortName).arg(serialPort->error()) << endl;
        return 1;
    }
    QByteArray readData = serialPort->readAll();
    while (serialPort->waitForReadyRead(5000))
        readData.append(serialPort->readAll());

    if (serialPort->error() == QSerialPort::ReadError) {
        standardOutput << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serialPort->errorString()) << endl;
        return 1;
    } else if (serialPort->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
        return 0;
    }

    standardOutput << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
    standardOutput << readData << endl;

    return 0;
}

