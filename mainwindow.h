#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "loginwindow.h"
#include "settingswindow.h"
#include "paymentwindow.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LoginWindow *lWnd = new LoginWindow(this);
    SettingsWindow *sWnd = new SettingsWindow(this);
    PaymentWindow *pWnd = new PaymentWindow(this);

private slots:
    void on_actionExit_triggered();
    void on_actionLogin_triggered();
    void on_btnPay_clicked();
};

#endif // MAINWINDOW_H
