#ifndef ONYMA_H
#define ONYMA_H


#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QtSql/QSqlRecord>



#include "queue/messagebuilder.h"
#include "queue/imessage.h"

#include "orm/test_table.h"
#include "queuebroker.h"

class Onyma {

public:
    Onyma();
    int connectDB(QMap<QString, QVariant> *params);
    QSqlQuery execSQL(QString *sql);
    QSqlQueryModel* getTable(QString *sql, QMap<QString, QVariant> *params);
    int disconnectDB();
    bool auth(QString *username, QString *password);
    void execCommand(QString command, QMap<QString, QVariant> &params);
private:
    QSqlDatabase db; // = QSqlDatabase::addDatabase("QPSQL", "onyma");
    bool authentificated = false;
    bool connected = false;
    QMap<QString, int> commandMap;
};

#endif // ONYMA_H
