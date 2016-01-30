#ifndef ONYMA_H
#define ONYMA_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>


class Onyma : public QObject
{
    Q_OBJECT
public:
    explicit Onyma(QObject *parent = 0);
    int connectDB();
    QSqlQuery execSQL(QString *sql, bool needAuth);
    QSqlQueryModel* getTable(QString *sql, bool needAuth);
    int disconnectDB();

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI", "onyma");

signals:

public slots:
};

#endif // ONYMA_H
