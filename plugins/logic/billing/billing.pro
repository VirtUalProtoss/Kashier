
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
    TARGET = logic_billing_onymad
} else {
    TARGET = logic_billing_onyma
} # CONFIG(debug, debug|release)

VERSION = 0.0.1
