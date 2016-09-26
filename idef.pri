CONFIG += c++11 plugin

QT -= gui

APPDIR = $$IN_PWD
INCLUDEPATH += . \
    $$APPDIR/common \
    $$APPDIR/common/queue
DEPENDPATH += $$APPDIR/lib
DESTDIR  = $$APPDIR/bin/plugins

DLIST = $$split(OUT_PWD, /)
DIR_HIGH = $$member(DLIST, -2)
DIR_LOW = $$member(DLIST, -1)
TARGET_NAME = $${DIR_HIGH}_$${DIR_LOW}

CONFIG(debug, debug|release) {
    win32: LIBS += -L$$APPDIR/lib/ #-lKashierCommond
    unix: LIBS += -L$$APPDIR/lib/ #-lKashierCommond #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = $${TARGET_NAME}d #_$${VERSION}
} else {
    win32: LIBS += -L$$APPDIR/lib/ #-lKashierCommon
    unix: LIBS += -L$$APPDIR/lib/ #-lKashierCommon #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = $${TARGET_NAME} #_$${VERSION}
} # CONFIG(debug, debug|release)


#message($$DIR_HIGH $$DIR_LOW)
