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
#include <QSqlRecord>

class Onyma : public QObject
{
    Q_OBJECT
public:
    explicit Onyma(QObject *parent = 0);
    int connectDB();
    QSqlQuery execSQL(QString *sql);
    QSqlQueryModel* getTable(QString *sql, QMap<QString, QVariant> *params);
    int disconnectDB();
    bool auth(QString *username, QString *password);

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI", "onyma");
    bool authentificated = false;
signals:

public slots:
};

#endif // ONYMA_H
