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

QString test() {

    QSqlError daoError; // = qx::dao::delete_all<test_table>();
    test_table_ptr test_table_1; test_table_1.reset(new test_table());

    //test_table_1->m_dogid = 12345678901;
    //test_table_1->m_name = "test_dog1";
    //daoError = qx::dao::insert(test_table_1);

    //qx::QxSqlQuery query("WHERE test_table.dogid = :dogid");
    //query.bind(":dogid", test_table_1->m_dogid);

    list_test_table lst_tt;
    //daoError = qx::dao::fetch_by_query(query, lst_tt);
    daoError = qx::dao::fetch_all(lst_tt);
    QString sDump;
    sDump = qx::serialization::json::to_string(lst_tt);

    return sDump;
}

Onyma::Onyma(QObject *parent) : ILogic(parent) {
    //QSqlDatabase::addDatabase("QOCI", "onyma");
    //db = QSqlDatabase::addDatabase("QPSQL", "onyma");
    if (!connected)
        connectDB();
    run();
    //QMap<QString, QVariant> params;
    //execCommand("getPayments", params);
    //connect(SIGNAL(message(IMessage*)), SLOT(emit_message(IMessage*)));
}

int Onyma::connectDB() {
    qDebug() << "connectDB()";
    /*
    db.setHostName("10.110.32.148");
    db.setDatabaseName("onyma");
    db.setUserName("onyma_api");
    db.setPassword("onyma_api");
    */
    /*
    db.setHostName("192.168.0.10");
    db.setDatabaseName("proman");
    db.setUserName("proman");
    db.setPassword("proman_proman");
    connected = db.open();
    if (!connected) {
        QSqlError msgError = db.lastError();
        qDebug() << "error open db" << msgError.text() << endl;
        return 1;
    }
    */
    //QString username = "s.sobolevskiy";
    //QString password = "NjgZYX3J";
    //authentificated = auth(&username, &password);

    qx::QxSqlDatabase::getSingleton()->setDriverName("QPSQL");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName("proman");
    qx::QxSqlDatabase::getSingleton()->setHostName("192.168.0.10");
    qx::QxSqlDatabase::getSingleton()->setUserName("proman");
    qx::QxSqlDatabase::getSingleton()->setPassword("proman_proman");

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
    //foreach (QString key, params->keys()) {
    //    query.bindValue(key, params->value(key));
    //    qDebug() << query.boundValue(key).toString();
    //}


    QSqlQueryModel *model = new QSqlQueryModel();
    query.exec(QString("select * from test_table"));
    qDebug() << query.executedQuery();
    model->setQuery(query);

    if (query.isSelect()) {
    while (query.next()) {
        QSqlRecord row = query.record();
        QString data = "";
        for (int i = 0; i < row.count(); i++) {
            data += row.fieldName(i) + ":" + row.value(i).toString() + " | ";
        }
        qDebug() << data;
    }
    } else {
        qDebug() << "Not select!";
    }

    qDebug() << "Fetched rows:" << model->rowCount();
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
    return QString("Billing");
}


void Onyma::execCommand(QString command, QMap<QString, QVariant> params) {
    qDebug() << "Command:" << command << "Params:" << params;

    /*
    pays_sql = "select * from test_table";

    if (command == "getPayments") {
        QString param1;
        foreach (QString key, params.keys()) {
            param1 = param1 + " and " + key + " = " + params.value(key).toString();
        }
        pays_sql = pays_sql.arg(param1);
        pays_sql = pays_sql.arg("");
    }
    qDebug() << pays_sql;
    QSqlQueryModel *model = getTable(&pays_sql, &params);
    */

    MessageBuilder* msgBuild = new MessageBuilder();
    msgBuild->setType(QString("Reply"));
    msgBuild->setSender(getName());
    //msgBuild->setHash(params["hash"]);
    //IMessage *msg = new IMessage();
    //msg->setHash(params["hash"].toString());
    //msg->setSender(getName());
    //msg->setType(QString("Reply"));
    //QString("Onyma"), QString("search"), params);
    QString result = test();
    qDebug("%s", qPrintable(result));
    msgBuild->setText(result);
    //emit message(msg);
    IMessage *msg = msgBuild->getMessage(params["target"].toString(), QString("getPayments"), params);
    emit message(msg);
    //test();
}

void Onyma::receive(IMessage *msg) {
    qDebug() << getName() << "receive message" << msg->toString();
    QStringList items = msg->getText().split("::");
    QString command = items[0];

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
        params["hash"] = msg->getHash();
        params["target"] = msg->getSender();
        execCommand(command, params);
    }
}

void Onyma::run()
{
    qDebug() << "run()";
    connectDB();
    QMap<QString, QVariant> params;
    execCommand(QString("getPayments"), params);
}

