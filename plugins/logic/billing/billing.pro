
CONFIG += c++11 plugin

TEMPLATE = lib
DESTDIR  = ../../../../bin/plugins
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue \
    ../../db \
    ../../../../../QxOrm/include

include(../../../../../QxOrm/QxOrm.pri)
HEADERS += onyma/onyma.h

SOURCES += onyma/onyma.cpp

CONFIG(debug, debug|release) {
    win32: LIBS += -L../../lib/ -lKashierCommond -lQxOrmd
    unix: LIBS += -L../../lib/ -lKashierCommond -lQxOrmd -Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_billing_onymad
} else {
    win32: LIBS += -L../../lib/ -lKashierCommon -lQxOrm
    unix: LIBS += -L../../lib/ -lKashierCommon -lQxOrm -Wl,-rpath,lib -Wl,-rpath,.
    TARGET = logic_billing_onyma
} # CONFIG(debug, debug|release)

VERSION = 0.0.1
