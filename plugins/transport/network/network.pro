QT += network

TEMPLATE = lib
VERSION = 0.1.0
include(../../../idef.pri)

HEADERS += socketadapter.h \
    transportnetwork.h

SOURCES += socketadapter.cpp \
    transportnetwork.cpp
