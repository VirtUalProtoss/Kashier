TEMPLATE = app
VERSION = 0.0.1
CONFIG -= plugin
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../idef.pri)
include(../common/defines.pri)
DESTDIR  = $$APPDIR/bin
DEFINES += IS_GUI
CONFIG(debug, debug|release) {
    LIBS += -lKashierCommond
    TARGET = kashier_guid
} else {
    LIBS += -lKashierCommon
    TARGET = kashier_gui
}

SOURCES += main.cpp
