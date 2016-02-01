
QT       += gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



SOURCES += \
    $$PWD/client.cpp \
    $$PWD/kashier.cpp \
    $$PWD/kkm.cpp \
    $$PWD/loginwindow.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/paymentwindow.cpp \
    $$PWD/settingswindow.cpp
    $$PWD/../objectmanager.cpp

HEADERS  += \
    $$PWD/client.h \
    $$PWD/kashier.h \
    $$PWD/kkm.h \
    $$PWD/loginwindow.h \
    $$PWD/mainwindow.h \
    $$PWD/paymentwindow.h \
    $$PWD/settingswindow.h \
    $$PWD/../objectmanager.h \
    $$PWD/../server/onyma.h

FORMS    += $$PWD/mainwindow.ui \
    $$PWD/loginwindow.ui \
    $$PWD/paymentwindow.ui \
    $$PWD/settingswindow.ui
