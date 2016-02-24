#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QDialog>


#include "mainwindow.h"
#include "../ilogic.h"


class GUI : public ILogic {
public:
    GUI(QObject *parent);
    QString getName();

    QString getWindow();
    QString getWindow(QString name);

    void addWindow(QMainWindow *window);
    void addWindow(QDialog *window);

private:
    QList<QDialog*> m_dialogs;
    QMainWindow* m_mainWindow;

};

#endif // GUI_H
