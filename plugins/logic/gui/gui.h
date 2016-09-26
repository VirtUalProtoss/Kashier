#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QDialog>
#include <QObject>
#include <QApplication>

#include "mainwindow.h"
#include "ilogic.h"
#include "plugininterface.h"



class GUI : public ILogic, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Kashier.Logic.GUI")
    Q_INTERFACES(PluginInterface)
public:
    explicit GUI(QObject *parent = 0);
    QString getName();

    QString getWindow();
    QString getWindow(QString name);

    void addWindow(QMainWindow *window);
    void addWindow(QDialog *window);
    void receive(IMessage *);
public slots:
    void on_init_complete();

private:
    QList<QDialog*> m_dialogs;
    QMainWindow* m_mainWindow;
    QApplication* m_app;
};

#endif // GUI_H
