#include "onyma.h"

/*
 *
    QDB2 — IBM DB2 (версия 7.1 и выше
    QIBASE — Borland InterBase
    QMYSQL — MySQL
    QOCI — Драйвер Oracle Call Interface
    QODBC — Open Database Connectivity (ODBC) — Microsoft SQL Server и другие ODBC-совместимые базы данных
    QPSQL — PostgreSQL (версия 7.3 и выше)
    QSQLITE2 — SQLite версии 2
    QSQLITE — SQLite версии 3
    QTDS — Драйвер Sybase Adaptive Server
 *
 * */

#include <iostream>
#include <QVariant>
#include <QDebug>
#include <QSqlRecord>

using namespace std;

Onyma::Onyma(QObject *parent) : QObject(parent)
{

}

int Onyma::connectDB()
{
    //db = QSqlDatabase::addDatabase("QOCI", "onyma");

    db.setHostName("10.110.32.148");
    db.setDatabaseName("onyma");
    db.setUserName("onyma_api");
    db.setPassword("onyma_api");
    bool ok = db.open();
    if (!ok) {
        QSqlError msgError = db.lastError();
        cout << "error open db" << endl; //msgError.text();
        return 1;
    }
    QSqlQuery authQuery("begin api_dog.auth('s.sobolevskiy','NjgZYX3J'); end;", db);
}

QSqlQuery Onyma::execSQL(QString *sql, bool needAuth=true)
{
    QSqlQuery query(*sql, db);
    int fieldNo = 0;
    while (query.next()) {
        QString name = query.value(fieldNo).toString();
        qDebug() << name << endl;
    }
    return query;
}

QSqlQueryModel* Onyma::getTable(QString *sql, bool needAuth=true)
{
    if (needAuth)
        QSqlQuery authQuery("begin api_dog.auth('s.sobolevskiy','NjgZYX3J'); end;", db);
    QSqlQueryModel *model = new QSqlQueryModel();
    cout << "Setting query..." << endl;
    model->setQuery(*sql, db);
    cout << "Querying data..." << endl;
    return model;
}

int Onyma::disconnectDB()
{
    db.close();
    db.removeDatabase("onyma");
    return 0;
}
