QT += multimedia

TEMPLATE = lib

CONFIG += staticlib

TARGET = canberra

DESTDIR = ../bin

HEADERS += \
    ../../quipchat/canberra/QSoundEffectNotification.h \
    ../../quipchat/canberra/SoundNotification.h

SOURCES += \
    ../../quipchat/canberra/QSoundEffectNotification.cpp \
    ../../quipchat/canberra/SoundNotification.cpp

win32 {
    HEADERS += \
        ../../quipchat/canberra/WindowsSoundNotification.h

    SOURCES += \
        ../../quipchat/canberra/WindowsSoundNotification.cpp
}

#unix {
#    HEADERS += \
#        ../../quipchat/canberra/CanberraSoundNotification.h

#    SOURCES += \
#        ../../quipchat/canberra/CanberraSoundNotification.cpp
#}

INCLUDEPATH += ../../quipchat/common

INCLUDEPATH += ../../qxmpp/src/client
INCLUDEPATH += ../../qxmpp/src/base

include(../qt5pro.pri)
