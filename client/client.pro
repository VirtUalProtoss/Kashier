
QT       += gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = client
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = _build
DESTDIR  = ../bin

CONFIG += c++11

SOURCES += main.cpp \
    client.cpp \
    ../common/logic/kkm/kkm.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    paymentwindow.cpp \
    settingswindow.cpp \
    clientsocketadapter.cpp \
    ../common/transport/isocketadapter.cpp \
    ../common/transport/socketadapter.cpp \
    ../common/queue/imessagebody.cpp \
    ../common/queue/imessagetype.cpp \
    ../common/queue/imessage.cpp \
    ../common/queue/imessagesender.cpp \
    ../common/queue/imessagereceiver.cpp \
    ../common/queue/query.cpp \
    ../common/logic/local/local.cpp \
    ../common/queue/iqueuebroker.cpp \
    ../common/queue/queuebroker.cpp \
    ../common/logic/ilogic.cpp \
    ../common/transport/itransport.cpp \
    ../common/logic/gui/gui.cpp \
    ../common/queue/messagebuilder.cpp \
    ../common/queue/packet.cpp \
    ../common/queue/subscribe.cpp \
    ../common/transport/transportlocal.cpp

HEADERS  += \
    client.h \
    ../common/logic/kkm/kkm.h \
    loginwindow.h \
    mainwindow.h \
    paymentwindow.h \
    settingswindow.h \
    clientsocketadapter.h \
    ../common/transport/isocketadapter.h \
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
    ../common/logic/gui/gui.h \
    ../common/queue/messagebuilder.h \
    ../common/queue/packet.h \
    ../common/queue/subscribe.h \
    ../common/transport/transportlocal.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    paymentwindow.ui \
    settingswindow.ui
