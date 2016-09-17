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

#include "ilogic.h"

#include "queue/messagebuilder.h"
#include "queue/imessage.h"

#include "orm/test_table.h"

#include "plugininterface.h"

class Onyma : public ILogic, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Kashier.Logic.Billing.Onyma")
    Q_INTERFACES(PluginInterface)
public:
    explicit Onyma(QObject *parent = 0);
    int connectDB();
    QSqlQuery execSQL(QString *sql);
    QSqlQueryModel* getTable(QString *sql, QMap<QString, QVariant> *params);
    int disconnectDB();
    bool auth(QString *username, QString *password);
    QString getName();
    void receive(IMessage *);
    ILogic* getInstance(ILogic* com) { return (ILogic*)this; };
    void run();

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
