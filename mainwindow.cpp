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
