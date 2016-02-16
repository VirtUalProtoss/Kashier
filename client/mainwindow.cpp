#include "mainwindow.h"
#include <QDebug>
#include <QVariant>
#include "clientsocketadapter.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), client(new Client(this)) {
    setupUi(this);
    edtPaymentsDate->setDate(QDate::currentDate());
}

MainWindow::~MainWindow() {

}

void MainWindow::search() {
    if (!edtSearch->text().isEmpty()) {
        QMap<QString, QVariant> params;
        params["text"] = edtSearch->text();
        client->send(QString("S"), &params);
    } else
        statusbar->showMessage(trUtf8("Нужно заполнить поле для поиска!"));
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}

void MainWindow::on_actionLogin_triggered() {
    lWnd->show();
}

void MainWindow::on_btnPay_clicked() {
    if (!edtSumma->text().isEmpty())
        pWnd->show();
}

void MainWindow::on_btnPaymentsWInfoRefresh_clicked() {
    QString sql = "select * from api_dogpayment where operid = 27452 and mdate = :mdate"; // to_date('29.01.16', 'dd.mm.yy')
    statusbar->showMessage("Обновляю список платежей...");
    QMap<QString, QVariant> params;
    params["mdate"] = edtPaymentsDate->date();
    params["operator"] = cmbPayOperator->currentText();

    client->send("OP", &params);
    //setPayments(onyma->getTable(&sql, &params));
    statusbar->showMessage("");
}

void MainWindow::on_viewPayments_doubleClicked() {
    QModelIndex idx = viewPayments->currentIndex();
    statusbar->showMessage(idx.data().toString());
    //tabWidget->setCurrentIndex(0);
}



void MainWindow::on_btnSearch_clicked() {
    search();
}

void MainWindow::on_edtSearch_returnPressed() {
    search();
}
