
CONFIG += c++11 plugin

QT -= gui

TEMPLATE = lib
DESTDIR  = ../../../../bin/plugins
DEPENDPATH += ../../../../lib
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue \
    ../../db \
    ../../../../../QxOrm/include

include(../../../../../QxOrm/QxOrm.pri)
HEADERS += onyma/onyma.h \
    onyma/orm/test_table.h

SOURCES += onyma/onyma.cpp \
    onyma/orm/test_table.cpp

CONFIG(debug, debug|release) {
    win32: LIBS += -L../../../../lib/ -lKashierCommond -lQxOrmd
    unix: LIBS += -L../../../../lib/ -lKashierCommond -lQxOrmd  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_billing_onymad
} else {
    win32: LIBS += -L../../../../lib/ -lQxOrm -lKashierCommon
    unix: LIBS += -L../../../../lib/ -lQxOrm -lKashierCommon  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_billing_onyma
} # CONFIG(debug, debug|release)

VERSION = 0.0.1
