#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T09:32:58
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kashier
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    paymentwindow.cpp \
    settingswindow.cpp \
    client.cpp \
    server.cpp \
    onyma.cpp \
    kkm.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    paymentwindow.h \
    settingswindow.h \
    client.h \
    server.h \
    onyma.h \
    kkm.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    paymentwindow.ui \
    settingswindow.ui
