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

Onyma::Onyma(QObject *parent) : ILogic(parent) {
    if (!connected)
        connectDB();
}

int Onyma::connectDB() {
    db.setHostName("10.110.32.148");
    db.setDatabaseName("onyma");
    db.setUserName("onyma_api");
    db.setPassword("onyma_api");
    connected = db.open();
    if (!connected) {
        QSqlError msgError = db.lastError();
        qDebug() << "error open db" << msgError.text() << endl;
        return 1;
    }
    //QString username = "s.sobolevskiy";
    //QString password = "NjgZYX3J";
    //auth(&username, &password);
    return 0;
}

QSqlQuery Onyma::execSQL(QString *sql) {
    QSqlQuery query(*sql, db);
    int fieldNo = 0;
    while (query.next()) {
        QString name = query.value(fieldNo).toString();
        qDebug() << name << endl;
    }
    return query;
}

QSqlQueryModel* Onyma::getTable(QString *sql, QMap<QString, QVariant> *params) {
    QSqlQuery query(db);
    query.prepare(*sql);
    foreach (QString key, params->keys()) {
        query.bindValue(key, params->value(key));
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    return model;
}

int Onyma::disconnectDB() {
    db.close();
    db.removeDatabase("onyma");
    return 0;
}

bool Onyma::auth(QString *username, QString *password) {
    QString auth_sql = "begin api_dog.auth('%1','%2'); commit; exception when others then rollback; end;";
    QSqlQuery authQuery(auth_sql.arg(*username).arg(*password), db);
    // TODO: Refactoring - check auth
    authentificated = true;
    return authentificated;
}

QString Onyma::getName() {
    return QString("Onyma");
}

void Onyma::receive(IMessage *msg) {
    qDebug() << getName() << "receive message" << msg->toString();
    QStringList items = msg->getText().split("::");
    QString command = items[0];
    qDebug() << "Command:" << command;
    if (items.length() > 1) {
        QMap<QString, QVariant> params;
        QStringList pList = items[1].split(";");
        foreach (QString param, pList) {
            if (param.length() == 0)
                continue;
            QStringList pArr = param.split("==");
            QString key = pArr[0];
            QString value = QString("");
            if (pArr.length() > 1)
                value = pArr[1];
            params[key] = value;
        }
        qDebug() << "Params:" << params;
    }
}

