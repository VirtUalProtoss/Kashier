#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "ui_settingswindow.h"

namespace Ui {
    class SettingsWindow;
}

class SettingsWindow : public QDialog, private Ui_SettingsWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

private:

};

#endif // SETTINGSWINDOW_H
