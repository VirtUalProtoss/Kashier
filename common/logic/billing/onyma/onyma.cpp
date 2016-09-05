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
    //QSqlDatabase::addDatabase("QOCI", "onyma");
    //db = QSqlDatabase::addDatabase("QPSQL", "onyma");
    if (!connected)
        connectDB();
}

int Onyma::connectDB() {

    /*
    db.setHostName("10.110.32.148");
    db.setDatabaseName("onyma");
    db.setUserName("onyma_api");
    db.setPassword("onyma_api");
    */
    db.setHostName("localhost");
    db.setDatabaseName("proman");
    db.setUserName("proman");
    db.setPassword("proman_proman");
    connected = db.open();
    if (!connected) {
        QSqlError msgError = db.lastError();
        qDebug() << "error open db" << msgError.text() << endl;
        return 1;
    }
    QString username = "s.sobolevskiy";
    QString password = "NjgZYX3J";
    //authentificated = auth(&username, &password);

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
    return QString("Onyma");
}

void Onyma::execCommand(QString command, QMap<QString, QVariant> params) {
    qDebug() << "Command:" << command << "Params:" << params;

    QString pays_sql = "\
        select * \
        from ( \
            select \
                pays.* \
                , decode( \
                    pays.bcid, \
                    0, decode(pays.vdog, 'Интернет', 1, 'Телевидение', 1, -1), \
                    24, decode(pays.vdog, 'Телефония', 2, 'LM', 3, 'Канал связи', 3, 'Прочие услуги НТ', 3, -1), \
                    25, decode(pays.vdog, 'Телефония', 2, -1), \
                    23, decode(pays.vdog, 'Телефония', 2, -1), \
                    22, decode(pays.vdog, 'Телефония', 5, -1), \
                    29, decode(pays.vdog, 'Телефония', 4, -1), \
                    26, decode(pays.vdog, 'Телефония', 6, -1), \
                    27, decode(pays.vdog, 'Телефония', 7, -1), \
                    -1 \
                ) section \
            from ( \
                select \
                    nvl(ab.cdate, ab.mdate) cdate \
                    , ab.billid \
                    , ab.mdate \
                    , round(ab.amount, 2) amount \
                    , ab.ntype \
                    , abt.remark bill_type \
                    , ab.bcid \
                    , ab.operid \
                    , ao.name oper_name \
                    , ab.dogid \
                    , adl.dogcode \
                    , adl.utid \
                    , ab.rmrk rmrk \
                    , nvl(api_func.get_add_dog_attrib(ab.dogid, 364, sysdate), 'Интернет') vdog \
                    , decode(adl.utid, 25, api_func.get_add_dog_attrib(adl.dogid, 291, sysdate), 26, api_func.get_add_dog_attrib(adl.dogid, 12, sysdate)) client \
                    , round(nvl(api_func.get_remainder(adl.dogid, sysdate), 0.0), 2) remainder \
                from api_dogpayment ab \
                join api_dog_list adl on ab.dogid = adl.dogid \
                join api_bill_type abt on ab.ntype = abt.ntype \
                join api_operators ao on ab.operid = ao.operid \
                where \
                    1 = 1 \
                    %1 \
            ) pays \
        ) \
        where \
            1 = 1 \
            %2 \
    ";

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


    //MessageBuilder* msgBuild = new MessageBuilder();
    //msgBuild->setType(QString("Reply"));
    //msgBuild->setSender(getName());
    //msgBuild->setHash(params["hash"]);
    IMessage* msg = new IMessage();
    msg->setHash(params["hash"].toString());
    msg->setSender(getName());
    //msg->setType(QString("Reply"));
    //QString("Onyma"), QString("search"), params);
    emit message(msg);
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
        execCommand(command, params);
    }
}

