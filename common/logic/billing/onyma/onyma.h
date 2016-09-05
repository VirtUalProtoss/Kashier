#ifndef ONYMA_H
#define ONYMA_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QtSql/QSqlRecord>

#include "../../ilogic.h"

#include "../common/queue/messagebuilder.h"

class Onyma : public ILogic {
    Q_OBJECT

public:
    explicit Onyma(QObject *parent = 0);
    int connectDB();
    QSqlQuery execSQL(QString *sql);
    QSqlQueryModel* getTable(QString *sql, QMap<QString, QVariant> *params);
    int disconnectDB();
    bool auth(QString *username, QString *password);
    QString getName();
    void receive(IMessage *);

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "onyma");
    bool authentificated = false;
    bool connected = false;
    QMap<QString, int> commandMap;

    void execCommand(QString command, QMap<QString, QVariant> params);
signals:
    void message(QString);
    void message(IMessage*);

public slots:
};

#endif // ONYMA_H
