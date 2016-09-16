
CONFIG += c++11

TEMPLATE = lib

target = db_orm

INCLUDEPATH += ../../../QxOrm/include/
LIBS += -L"../../lib"

include(../../../../QxOrm/QxOrm.pri)

CONFIG(debug, debug|release) {
    LIBS += -l"QxOrmd"
} else {
    LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
    PRECOMPILED_HEADER = ./precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)
