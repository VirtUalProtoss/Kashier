#include "gui.h"
#include "queuebroker.h"

#include <QDebug>


GUI::GUI(QObject *parent) : ILogic(parent) {
    m_mainWindow = new MainWindow();
    m_mainWindow->show();
    connect(m_mainWindow, SIGNAL(message(IMessage*)), SLOT(emit_message(IMessage*)));
    connect(this, SIGNAL(init_complete()), this, SLOT(on_init_complete()));

}

QString GUI::getName() {
    return QString("GUI");
}

QString GUI::getWindow() {
    return QString("GUI<main>");
}

QString GUI::getWindow(QString name) {
    QString mName;
    foreach (QDialog *wnd, m_dialogs) {
        if (name == wnd->objectName())
            mName = wnd->objectName();
    }

    return QString("GUI<" + mName + ">");
}

void GUI::addWindow(QMainWindow *window) {
    m_mainWindow = window;
}

void GUI::addWindow(QDialog *window) {
    m_dialogs.append(window);
}

void GUI::receive(IMessage *msg) {
    qDebug() << "GUI" << getName() << "receive message" << msg->toString();
}

void GUI::on_init_complete() {
    m_broker = static_cast<QueueBroker*>(this->parent());
    QString sub = QString("GUI<MainWindow>;Network::Billing;Query;Persist");
    subscribe(sub);
}
