
TEMPLATE = lib
VERSION = 0.0.1
include(../../../idef.pri)
INCLUDEPATH += . \
    ../../db \
    ../../../../../QxOrm/include

include(../../../../../QxOrm/QxOrm.pri)
HEADERS += onyma/onyma.h \
    onyma/orm/test_table.h

SOURCES += onyma/onyma.cpp \
    onyma/orm/test_table.cpp

CONFIG(debug, debug|release) {
    win32: LIBS += -lQxOrmd -lKashierCommond
    unix: LIBS += -lQxOrmd -lKashierCommond
} else {
    win32: LIBS += -lQxOrm -lKashierCommon
    unix: LIBS += -lQxOrm -lKashierCommon
}
