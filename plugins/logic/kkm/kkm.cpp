#include "kkm.h"

command commands[200] = {
    {0x01, "", 50}, {0x02, "", 50}, {0x03, "", 50}, {0x04, "", 50}, {0x05, "", 50}, {0x06, "", 50},
    {0x07, "", 50}, {0x08, "", 50}, {0x09, "", 50}, {0x0a, "", 50}, {0x0b, "", 50}, {0x0c, "", 50},

    {0x0d, "Фискализация (перерегистрация)", 50000},

    {0x0e, "", 50}, {0x0f, "", 50},

    {0x10, "Короткий запрос состояния ФР", 5000},
    {0x11, "Запрос состояния ФР", 5000},
    {0x12, "Печать жирной строки", 2000},
    {0x13, "Гудок", 500},

    {0x14, "", 50}, {0x15, "", 50},

    {0x16, "Технологическое обнуление", 50000},
    {0x17, "Печать строки", 1500},
    {0x18, "Печать заголовка документа", 1500},

    {0x19, "", 50}, {0x1a, "", 50}, {0x1b, "", 50}, {0x1c, "", 50}, {0x1d, "", 50},

    {0x1e, "Запись таблицы", 5000},
    {0x1f, "Чтение таблицы", 5000},

    {0x20, "", 50}, {0x21, "", 50},

    {0x22, "Программирование даты", 500},
    {0x23, "Подтверждение программирования даты", 500},
    {0x24, "Инициализация таблиц начальными значениями", 5000},
    {0x25, "Отрезка чека", 1500},

    {0x26, "", 50},

    {0x27, "Общее гашение", 5000},

    {0x28, "", 50},

    {0x29, "Протяжка", 500},

    {0x2a, "", 50}, {0x2b, "", 50}, {0x2c, "", 50}, {0x2d, "", 50}, {0x2e, "", 50},

    {0x2f, "Печать строки данным шрифтом", 500},

    {0x30, "", 50}, {0x31, "", 50}, {0x32, "", 50}, {0x33, "", 50}, {0x34, "", 50}, {0x35, "", 50},
    {0x36, "", 50}, {0x37, "", 50}, {0x38, "", 50}, {0x39, "", 50}, {0x3a, "", 50}, {0x3b, "", 50},
    {0x3c, "", 50}, {0x3d, "", 50}, {0x3e, "", 50}, {0x3f, "", 50},

    {0x40, "Суточный отчет без гашения", 5000},
    {0x41, "Суточный отчет с гашением", 5000},
    {0x42, "Отчет по секциям", 5000},
    {0x43, "Отчет по налогам", 5000},

    {0x44, "", 50}, {0x45, "", 50}, {0x46, "", 50}, {0x47, "", 50}, {0x48, "", 50}, {0x49, "", 50},
    {0x4a, "", 50}, {0x4b, "", 50}, {0x4c, "", 50}, {0x4d, "", 50}, {0x4e, "", 50}, {0x4f, "", 50},

    {0x50, "Внесение", 500},
    {0x51, "Выплата", 500},

    {0x52, "", 50}, {0x53, "", 50}, {0x54, "", 50}, {0x55, "", 50}, {0x56, "", 50}, {0x57, "", 50},
    {0x58, "", 50}, {0x59, "", 50}, {0x5a, "", 50}, {0x5b, "", 50}, {0x5c, "", 50}, {0x5d, "", 50},
    {0x5e, "", 50}, {0x5f, "", 50}, {0x60, "", 50}, {0x61, "", 50}, {0x62, "", 50},

    {0x63, "Запрос даты последней записи в ФП", 50},
    {0x64, "Запрос диапазона дат и смен", 50},

    {0x65, "", 50}, {0x66, "", 50}, {0x67, "", 50}, {0x68, "", 50}, {0x69, "", 50}, {0x6a, "", 50},
    {0x6b, "", 50}, {0x6c, "", 50}, {0x6d, "", 50}, {0x6e, "", 50}, {0x6f, "", 50}, {0x70, "", 50},
    {0x71, "", 50}, {0x72, "", 50}, {0x73, "", 50}, {0x74, "", 50}, {0x75, "", 50}, {0x76, "", 50},
    {0x77, "", 50}, {0x78, "", 50}, {0x79, "", 50}, {0x7a, "", 50}, {0x7b, "", 50}, {0x7c, "", 50},
    {0x7d, "", 50}, {0x7e, "", 50}, {0x7f, "", 50}, {0x80, "", 50}, {0x81, "", 50}, {0x82, "", 50},
    {0x83, "", 50}, {0x84, "", 50},

    {0x85, "Закрытие чека", 5000},
    {0x86, "Скидка", 500},
    {0x87, "Надбавка", 500},
    {0x88, "Аннулирование чека", 1500},
    {0x89, "Подытог чека", 1500},

    {0x8a, "", 50}, {0x8b, "", 50}, {0x8c, "", 50},

    {0x8d, "Открыть чек", 1500},

    {0x8e, "", 50}, {0x8f, "", 50}, {0x90, "", 50}, {0x91, "", 50}, {0x92, "", 50}, {0x93, "", 50},
    {0x94, "", 50}, {0x95, "", 50}, {0x96, "", 50}, {0x97, "", 50}, {0x98, "", 50}, {0x99, "", 50},
    {0x9a, "", 50}, {0x9b, "", 50}, {0x9c, "", 50}, {0x9d, "", 50}, {0x9e, "", 50}, {0x9f, "", 50},
    {0xa0, "", 50}, {0xa1, "", 50}, {0xa2, "", 50}, {0xa3, "", 50}, {0xa4, "", 50}, {0xa5, "", 50},

    {0xa6, "Контрольная лента из ЭКЛЗ по номеру смены", 15000},

    {0xa7, "", 50},

    {0xa8, "Итог активизации ЭКЛЗ", 5000},
    {0xa9, "Активизация ЭКЛЗ", 15000},
    {0xaa, "Закрытие архива ЭКЛЗ", 5000},
    {0xab, "Запрос регистрационного номера ЭКЛЗ", 500},
    {0xac, "Прекращение ЭКЛЗ", 15000},
    {0xad, "Запрос состояния по коду 1 ЭКЛЗ", 5000},
    {0xae, "Запрос состояния по коду 2 ЭКЛЗ", 5000},

    {0xaf, "", 50},

    {0xb0, "Продолжение печати", 50},

    {0xb1, "", 50},

    {0xb2, "Инициализация архива ЭКЛЗ", 15000},

    {0xb3, "", 50}, {0xb4, "", 50}, {0xb5, "", 50}, {0xb6, "", 50}, {0xb7, "", 50}, {0xb8, "", 50},
    {0xb9, "", 50},

    {0xba, "Запрос в ЭКЛЗ итогов смены по номеру смены", 5000},

    {0xbb, "", 50}, {0xbc, "", 50}, {0xbd, "", 50}, {0xbe, "", 50}, {0xbf, "", 50}, {0xc0, "", 50},

    {0xc1, "Печать графики", 5000},
    {0xc2, "Печать штрих-кода", 5000},
    {0xc3, "Печать расширенной графики", 5000},
    {0xc4, "Загрузка расширенной графики", 5000},
    {0xc5, "Печать линии", 5000},

    {0xc6, "", 50}, {0xc7, "", 50}, {0xc8, "", 50}
};

QString errorCodes[200] = {
    "Ошибок нет", "", "", "", "", "", "", "", "", "", //0
    "", "", "", "", "", "", "", "", "", "", //10
    "", "", "", "", "", "", "", "", "", "", //20
    "", "", "", "", "", "", "", "", "", "", //30
    "", "", "", "", "", "", "", "", "", "", //40
    "",
    "Некорректные параметры в команде", "", "", "",
    "Команда не поддерживается в данной реализации ФР", "", "", "", "", //50
    "", "", "", "", "", "", "", "", "", "", //60
    "", "", "", "",
    "Открыт чек, операция невозможна", "", "", "",
    "Смена превысила 24 часа", "", //70
    "", "", "", "", "", "", "", "", "", "", //80
    "", "", "", "", "", "", "", "", "", "", //90
    "", "", "", "", "", "", "", "", "", "", //100
    "", "", "", "", "", "", "", "", "", "", //110
    "", "", "", "", "", "", "", "", "", "", //120
    "", "", "", "", "", "", "", "", "", "", //130
    "", "", "", "", "", "", "", "", "", "", //140
    "", "", "", "", "", "", "", "", "", "", //150
    "", "", "", "", "", "", "", "", "", "", //160
    "", "", "", "", "", "", "", "", "", "", //170
    "", "", "", "", "", "", "", "", "", "", //180
    "", "", "", "", "", "", "", "", "", "" //190
};

KKM::KKM(QObject *parent) : ILogic(parent) {
    // Test!
    //serialPort->setPortName(serialPortName);
    //serialPort->setBaudRate(serialPortBaudRate);
    //int oRes = openSerialPort();
    //if (oRes != 0)
    //    return;
}

int KKM::openSerialPort() {
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
    }
    else if (serialPort->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
        return 0;
    }

    standardOutput << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
    standardOutput << readData << endl;

    return 0;
}

QByteArray KKM::read(int timeout) {
    QByteArray readData = serialPort->readAll();
    while (serialPort->waitForReadyRead(timeout))
        readData.append(serialPort->readAll());

    if (serialPort->error() == QSerialPort::ReadError) {
        qDebug() << tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serialPort->errorString()) << endl;
    }
    else if (serialPort->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        qDebug() << tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
    }
    return readData;
}

bool KKM::initConnection(int retryCount=10) {
    if (retryCount < 0) {
        QByteArray data;
        data.append(ACK+'0');
        data.append(ENQ+'0');
        serialPort->write(data);
        return -1;
    }
    try {
        QByteArray data;
        data.append(ENQ+'0');
        serialPort->write(data);
        qDebug() << "sended: " << data << endl;
    }
    catch(...) {
        if (serialPort->error() && QSerialPort::ReadError) {
            qDebug() << tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serialPort->errorString()) << endl;
        }
        else if (serialPort->error() == QSerialPort::TimeoutError) {
            qDebug() << tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
        }
        else {
            qDebug() << tr("Failed to init KKM from port %1, error: %2").arg(serialPortName).arg(serialPort->errorString()) << endl;
        }
    }
    QByteArray readData = read(50);

    if (!readData.isEmpty()) {
        if (readData.length() == 1) {
            switch (readData[0]) {
                case ACK:
                    // FR prepary reply, need wait
                    break;
                case NAK:
                    // FR ready to work
                    ready = true;
                    break;
                default:
                    // no connect?
                    break;
            };
        }
        else {
            // Reset FR state
            QByteArray data;
            data.append(ACK+'0');
            data.append(ENQ+'0');
            serialPort->write(data);
            ready = true;
        }
    }
    else {
        ready = initConnection(retryCount-1);
    }

    return ready;
}

void KKM::beep()
{
    //if (!ready)
    //    if (!initConnection())
    //        return;
    QMap<QString, QVariant> params;
    execCommand(19, params);
}

QString KKM::getName() {
    return QString("KKM");
}

void KKM::getMessageBytes(int code, QByteArray &message, QByteArray &bytes) {
    //QByteArray stx = int2char(STX, 1, 16);
    //bytes.append(stx);
    bytes.append(STX+'0');
    bytes.append((message.length()+1)+'0');
    QByteArray p = int2char(code, 4, 10);
    bytes.append(p);
    bytes.append(message);
    char xbyte = '0';
    for (int i = 1; i < bytes.length(); i++) {
        xbyte ^= bytes.at(i);
    }
    bytes.append(xbyte);
}

QByteArray KKM::int2char(int value, int length=4, int base=10) {
    char *str = new char[length];
    for (int i=0; i<length; i++) {
        str[i] = 0;
    }
    QByteArray *bytes = new QByteArray(str);
    for(int i = 0; i != sizeof(value); ++i) {
        bytes->append((char)((value & (0xFF << (i*8))) >> (i*8)));
    }

    return *bytes;
}

bool KKM::execCommand(int code, QMap<QString, QVariant> &params) {
    int password = 30;
    QByteArray byteStream, message;
    QByteArray p = int2char(password, 4, 10);
    byteStream.append(p);

    foreach (QString key, params.keys()) {
        message.append(params.value(key).toChar());
    }

    if (message.length() > 0)
        byteStream.append(message);

    QByteArray msgBytes;
    getMessageBytes(code, byteStream, msgBytes);

    //serialPort->write(msgBytes);
    qDebug() << "sended: " << msgBytes << msgBytes.toHex() << endl;
    //int timeout = commands[code].timeout;
    //QByteArray reply = read(timeout);
    //qDebug() << "received: " << reply << " timeout: " << timeout << endl;
    return true;
}
