QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11 plugin

DESTDIR  = ../../../../bin/plugins
DEPENDPATH += ../../../../lib
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue

CONFIG(debug, debug|release) {
    win32: LIBS += -L../../../../lib/ -lKashierCommond
    unix: LIBS += -L../../../../lib/ -lKashierCommond  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_guid
} else {
    win32: LIBS += -L../../../../lib/ -lKashierCommon
    unix: LIBS += -L../../../../lib/ -lKashierCommon  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_gui
} # CONFIG(debug, debug|release)

VERSION = 0.0.1

TEMPLATE = lib
OBJECTS_DIR = _build
DESTDIR  = ../../bin

CONFIG += c++11

SOURCES += main.cpp \
    client.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    paymentwindow.cpp \
    settingswindow.cpp \
    gui.cpp

HEADERS  += \
    client.h \
    loginwindow.h \
    mainwindow.h \
    paymentwindow.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    paymentwindow.ui \
    settingswindow.ui

