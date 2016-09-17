CONFIG += c++11
TEMPLATE = app
QT -= gui
SOURCES += main.cpp
INCLUDEPATH += ../common
DESTDIR  = ../../bin
DEPENDPATH += $$PWD/../common

include(../common/defines.pri)

CONFIG(debug, debug|release) {
    # Подключаем debug-версии библиотек для разных платформ
    win32: LIBS += -L../../lib/ -lKashierCommond
    unix: LIBS += -L../../lib/ -lKashierCommond -Wl,-rpath,lib -Wl,-rpath,.
    TARGET = kashierd
} else {
    # Подключаем release-версии библиотек для разных платформ
    win32: LIBS += -L../../lib/ -lKashierCommon
    unix: LIBS += -L../../lib/ -lKashierCommon -Wl,-rpath,lib -Wl,-rpath,.
    TARGET = kashier
}
