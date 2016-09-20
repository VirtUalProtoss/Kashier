
CONFIG += c++11 plugin

QT -= gui

TEMPLATE = lib
DESTDIR  = ../../../../bin/plugins
DEPENDPATH += ../../../../lib
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue

HEADERS += transportlocal.h

SOURCES += transportlocal.cpp

CONFIG(debug, debug|release) {
    win32: LIBS += -L../../../../lib/
    unix: LIBS += -L../../../../lib/  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = transport_locald
} else {
    win32: LIBS += -L../../../../lib/
    unix: LIBS += -L../../../../lib/  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = transport_local
} # CONFIG(debug, debug|release)

VERSION = 0.0.1
