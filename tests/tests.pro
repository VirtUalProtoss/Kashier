#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T12:58:01
#
#-------------------------------------------------

QT       += core testlib gui

#QT       -= gui
include(../idef.pri)
include(../common/defines.pri)

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    test_subscribe.cpp \
    test_broker.cpp

HEADERS += \
    test_subscribe.h \
    test_broker.h




CONFIG -= plugin
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
