#include "gui.h"


GUI::GUI(QObject *parent) : ILogic(parent) {
    m_mainWindow = new MainWindow();
    m_mainWindow->show();
    connect(m_mainWindow, SIGNAL(message(IMessage*)), SLOT(emit_message(IMessage*)));
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
