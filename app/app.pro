TEMPLATE = app
VERSION = 0.0.1
QT -= gui
CONFIG -= plugin
include(../idef.pri)
include(../common/defines.pri)
DESTDIR  = $$APPDIR/bin

CONFIG(debug, debug|release) {
    TARGET = kashierd
} else {
    TARGET = kashier
}

SOURCES += main.cpp
