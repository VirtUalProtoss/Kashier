
#include <QApplication>

#include "client.h"

#include <QObject>
#include <QTextStream>
#include <QString>
#include <QDebug>

QByteArray int2char(int value, int length=4, int base=10) {
    char *str = new char[length];
    for (int i=0; i<length; i++) {
        str[i] = 0;
    }
    QByteArray *bytes = new QByteArray(str);
    for(int i = 0; i != sizeof(value); ++i)
    {
        bytes->append((char)((value & (0xFF << (i*8))) >> (i*8)));
    }

    return *bytes;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Client client;
    client.initComponents();
    client.prepareSubcribes();
    client.publishComponents();
    return a.exec();
}
