#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>
#include "ui_paymentwindow.h"

namespace Ui {
    class PaymentWindow;
}

class PaymentWindow : public QDialog, private Ui_PaymentWindow {
    Q_OBJECT

public:
    explicit PaymentWindow(QWidget *parent = 0);
    ~PaymentWindow();

private:

};

#endif // PAYMENTWINDOW_H
