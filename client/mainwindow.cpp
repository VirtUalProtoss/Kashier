#include "mainwindow.h"
#include <QDebug>
#include <QVariant>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    edtPaymentsDate->setDate(QDate::currentDate());
}

MainWindow::~MainWindow() {

}

void MainWindow::search() {
    if (!edtSearch->text().isEmpty()) {
        QMap<QString, QVariant> params;
        params["type"] = cmbSearchSelect->currentText();
        params["text"] = edtSearch->text();
        MessageBuilder* msgBuild = new MessageBuilder(this);
        msgBuild->setType(QString("Query"));
        msgBuild->setSender(getName());
        emit message(msgBuild->getMessage(QString("Onyma"), QString("search"), params));
    } else
        statusbar->showMessage(trUtf8("Нужно заполнить поле для поиска!"));
}

QString MainWindow::getName() {
    return QString("GUI<" + objectName() + ">");
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
    else
        statusbar->showMessage(trUtf8("Нужно ввести сумму платежа!"));
}

void MainWindow::on_btnPaymentsWInfoRefresh_clicked() {
    statusbar->showMessage("Обновляю список платежей...");
    QMap<QString, QVariant> params;
    params["mdate"] = edtPaymentsDate->date();
    params["operator"] = cmbPayOperator->currentText();
    MessageBuilder* msgBuild = new MessageBuilder(this);
    msgBuild->setType(QString("Query"));
    msgBuild->setSender(getName());
    emit message(msgBuild->getMessage(QString("Onyma"), QString("getPayments"), params));
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
