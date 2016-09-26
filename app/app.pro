TEMPLATE = app
VERSION = 0.0.1
CONFIG -= plugin
include(../idef.pri)
include(../common/defines.pri)
DESTDIR  = $$APPDIR/bin

CONFIG(debug, debug|release) {
    LIBS += -lKashierCommond
    TARGET = kashierd
} else {
    LIBS += -lKashierCommon
    TARGET = kashier
}

SOURCES += main.cpp
