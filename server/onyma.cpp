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


using namespace std;

Onyma::Onyma(QObject *parent) : QObject(parent)
{

}

int Onyma::connectDB()
{
    db.setHostName("10.110.32.148");
    db.setDatabaseName("onyma");
    db.setUserName("onyma_api");
    db.setPassword("onyma_api");
    bool ok = db.open();
    if (!ok) {
        QSqlError msgError = db.lastError();
        qDebug() << "error open db" << msgError.text() << endl;
        return 1;
    }
    QString username = "s.sobolevskiy";
    QString password = "NjgZYX3J";
    auth(&username, &password);
    return 0;
}

QSqlQuery Onyma::execSQL(QString *sql)
{
    QSqlQuery query(*sql, db);
    int fieldNo = 0;
    while (query.next()) {
        QString name = query.value(fieldNo).toString();
        qDebug() << name << endl;
    }
    return query;
}

QSqlQueryModel* Onyma::getTable(QString *sql, QMap<QString, QVariant> *params)
{
    QSqlQuery query(db);
    query.prepare(*sql);
    foreach (QString key, params->keys())
    {
        query.bindValue(key, params->value(key));
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    return model;
}

int Onyma::disconnectDB()
{
    db.close();
    db.removeDatabase("onyma");
    return 0;
}

bool Onyma::auth(QString *username, QString *password)
{
    QString auth_sql = "begin api_dog.auth('%1','%2'); end;";
    QSqlQuery authQuery(auth_sql.arg(*username).arg(*password), db);
    authentificated = true;
    return authentificated;
}
