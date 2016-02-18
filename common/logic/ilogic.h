#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>


class ILogic : public QObject {
    Q_OBJECT
public:
    explicit ILogic(QObject *parent);
    virtual QString getName();
    virtual void setName(QString &name);
signals:

public slots:
private:
    QString name = "ILogic";
};

#endif // ILOGIC_H
