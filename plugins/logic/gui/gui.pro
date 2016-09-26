QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
VERSION = 0.0.1
include(../../../idef.pri)

SOURCES += gui.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    paymentwindow.cpp \
    settingswindow.cpp

HEADERS  += gui.h \
    loginwindow.h \
    mainwindow.h \
    paymentwindow.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    paymentwindow.ui \
    settingswindow.ui
