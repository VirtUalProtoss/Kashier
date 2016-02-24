######################################################################
# Automatically generated by qmake (2.01a) ?? ??? 11 16:31:00 2014
######################################################################

TEMPLATE = app
TARGET = server
DEPENDPATH += .
INCLUDEPATH += .

OBJECTS_DIR = _build
DESTDIR  = ../bin

CONFIG += c++11

QT += network sql

# Input
SOURCES += main.cpp \
    ../common/logic/billing/onyma/onyma.cpp \
    ../common/logic/ats/openmn.cpp \
    service.cpp \
    ../common/transport/isocketadapter.cpp \
    serversocketadapter.cpp \
    ../common/transport/socketadapter.cpp \
    ../common/queue/imessagebody.cpp \
    ../common/queue/imessagetype.cpp \
    ../common/queue/imessage.cpp \
    ../common/queue/imessagesender.cpp \
    ../common/queue/imessagereceiver.cpp \
    ../common/queue/query.cpp \
    ../common/logic/local/local.cpp \
    ../common/queue/queuebroker.cpp \
    ../common/logic/ilogic.cpp \
    ../common/transport/itransport.cpp \
    ../common/queue/iqueuebroker.cpp \
    ../common/queue/packet.cpp \
    ../common/queue/messagebuilder.cpp

HEADERS += \
    ../common/logic/billing/onyma/onyma.h \
    ../common/logic/ats/openmn.h \
    service.h \
    ../common/transport/isocketadapter.h \
    serversocketadapter.h \
    ../common/transport/socketadapter.h \
    ../common/queue/imessagebody.h \
    ../common/queue/imessagetype.h \
    ../common/queue/imessage.h \
    ../common/queue/imessagesender.h \
    ../common/queue/imessagereceiver.h \
    ../common/queue/iqueuebroker.h \
    ../common/queue/query.h \
    ../common/logic/local/local.h \
    ../common/queue/queuebroker.h \
    ../common/logic/ilogic.h \
    ../common/transport/itransport.h \
    ../common/queue/packet.h \
    ../common/queue/messagebuilder.h
