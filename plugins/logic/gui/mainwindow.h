#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "loginwindow.h"
#include "settingswindow.h"
#include "paymentwindow.h"

#include "../common/queue/messagebuilder.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, protected Ui_MainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LoginWindow *lWnd = new LoginWindow(this);
    SettingsWindow *sWnd = new SettingsWindow(this);
    PaymentWindow *pWnd = new PaymentWindow(this);
    void search();
    QString getName();

private slots:
    void on_actionExit_triggered();
    void on_actionLogin_triggered();
    void on_btnPay_clicked();
    void on_btnPaymentsWInfoRefresh_clicked();
    void on_viewPayments_doubleClicked();
    void on_btnSearch_clicked();
    void on_edtSearch_returnPressed();

signals:
    void message(QString, QMap<QString, QVariant>*);
    void message(IMessage*);
protected:

};

#endif // MAINWINDOW_H
