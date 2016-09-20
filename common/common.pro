TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += . ./queue

#OBJECTS_DIR = _build
DESTDIR  = ../../lib

CONFIG += c++11

#CONFIG(release, release): DEFINES += QT_NO_DEBUG_OUTPUT

QT -= gui

#QT_MESSAGE_PATTERN="%{file} %{line} %{message}"


CONFIG(debug, debug|release) {
    TARGET = KashierCommond
} else {
    TARGET = KashierCommon
} # CONFIG(debug, debug|release)

VERSION = 0.0.1

include(defines.pri)

# Input
SOURCES += service.cpp \
    queue/imessagebody.cpp \
    queue/imessagetype.cpp \
    queue/imessage.cpp \
    queue/imessagesender.cpp \
    queue/imessagereceiver.cpp \
    queue/query.cpp \
    queue/queuebroker.cpp \
    queue/packet.cpp \
    queue/messagebuilder.cpp \
    queue/subscribe.cpp \
    ilogic.cpp \
    itransport.cpp \
    plugininterface.cpp \
    queue/uri.cpp

HEADERS += service.h \
    queue/imessagebody.h \
    queue/imessagetype.h \
    queue/imessage.h \
    queue/imessagesender.h \
    queue/imessagereceiver.h \
    queue/query.h \
    queue/queuebroker.h \
    queue/packet.h \
    queue/messagebuilder.h \
    queue/subscribe.h \
    kashiercommon_global.h \
    ilogic.h \
    itransport.h \
    plugininterface.h \
    queue/uri.h
