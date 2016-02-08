#include "mainwindow.h"
#include <QDebug>
#include <QVariant>
#include "clientsocketadapter.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), pSock(new ClientSocketAdapter(this)) {
    setupUi(this);
    edtPaymentsDate->setDate(QDate::currentDate());
    connect(pSock, SIGNAL(message(QString)), SLOT(on_message(QString)));
}

MainWindow::~MainWindow() {

}

void MainWindow::search() {
    if (!edtSearch->text().isEmpty()) {
        QMap<QString, QVariant> params;
        params["text"] = edtSearch->text();
        sendCommand("S", &params);
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

void MainWindow::on_message(QString text) {
    statusbar->showMessage(text);
    qDebug() << text << endl;
}

void MainWindow::on_send() {

}

/*
void MainWindow::setPayments(QSqlQueryModel *model) {
    //tblPayments->setModel(model);
    viewPayments->setModel(model);
    viewPayments->show();
}
*/

void MainWindow::on_btnPaymentsWInfoRefresh_clicked() {
    QString sql = "select * from api_dogpayment where operid = 27452 and mdate = :mdate"; // to_date('29.01.16', 'dd.mm.yy')
    statusbar->showMessage("Обновляю список платежей...");
    QMap<QString, QVariant> params;
    params["mdate"] = edtPaymentsDate->date();
    params["operator"] = cmbPayOperator->currentText();

    sendCommand("OP", &params);
    //setPayments(onyma->getTable(&sql, &params));
    statusbar->showMessage("");
}

void MainWindow::on_viewPayments_doubleClicked() {
    QModelIndex idx = viewPayments->currentIndex();
    statusbar->showMessage(idx.data().toString());
    //tabWidget->setCurrentIndex(0);
}

void MainWindow::sendCommand(QString command, QMap<QString, QVariant> *params) {
    QString streamData;
    foreach (QString key, params->keys()) {
        streamData += key + "->" + params->value(key).toString() + ",";
    }
    pSock->sendString(command + ":" + streamData);
}

void MainWindow::on_btnSearch_clicked() {
    search();
}

void MainWindow::on_edtSearch_returnPressed() {
    search();
}

/*
void MainWindow::setOnyma(Onyma *olink) {
    onyma = olink;
}
*/
