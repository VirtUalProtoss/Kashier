#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QDialog>


#include "mainwindow.h"
#include "ilogic.h"
#include "plugininterface.h"


class GUI : public ILogic, public PluginInterface {
    Q_PLUGIN_METADATA(IID "Kashier.Transport.Network")
    Q_INTERFACES(PluginInterface)
public:
    GUI(QObject *parent);
    QString getName();

    QString getWindow();
    QString getWindow(QString name);

    void addWindow(QMainWindow *window);
    void addWindow(QDialog *window);
    void receive(IMessage *);

private:
    QList<QDialog*> m_dialogs;
    QMainWindow* m_mainWindow;

};

#endif // GUI_H
