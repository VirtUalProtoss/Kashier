#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionLogin_triggered()
{
    lWnd->show();
}

void MainWindow::on_btnPay_clicked()
{
    if (!edtSumma->text().isEmpty())
        pWnd->show();
}

void MainWindow::setPayments(QSqlQueryModel *model)
{
    //tblPayments->setModel(model);
    viewPayments->setModel(model);
    viewPayments->show();
}

void MainWindow::on_btnPaymentsWInfoRefresh_clicked()
{
    QString sql = "select * from api_dogpayment where operid = 27452 and mdate = to_date('29.01.16', 'dd.mm.yy')";
    //QString sql = "select login from api_operators";
    //onyma->execSQL(&sql, true);
    setPayments(onyma->getTable(&sql, true));
}

void MainWindow::setOnyma(Onyma *olink)
{
    onyma = olink;
}
