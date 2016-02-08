#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "ui_loginwindow.h"

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog, private Ui_LoginWindow {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:

};

#endif // LOGINWINDOW_H
