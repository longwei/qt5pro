QT += network widgets

TEMPLATE = lib

CONFIG += staticlib

TARGET = qtsparkle

DESTDIR = ../bin

FORMS += \
    ../../quipchat/qtsparkle/src/updatedialog.ui

HEADERS += \
    ../../quipchat/qtsparkle/src/appcast.h \
    ../../quipchat/qtsparkle/src/appcast_fwd.h \
    ../../quipchat/qtsparkle/src/common.h \
    ../../quipchat/qtsparkle/src/compareversions.h \
    ../../quipchat/qtsparkle/src/followredirects.h \
    ../../quipchat/qtsparkle/src/uicontroller.h \
    ../../quipchat/qtsparkle/src/updatechecker.h \
    ../../quipchat/qtsparkle/src/updatedialog.h \
    ../../quipchat/qtsparkle/src/updater.h

SOURCES += \
    ../../quipchat/qtsparkle/src/appcast.cpp \
    ../../quipchat/qtsparkle/src/common.cpp \
    ../../quipchat/qtsparkle/src/compareversions.cpp \
    ../../quipchat/qtsparkle/src/followredirects.cpp \
    ../../quipchat/qtsparkle/src/uicontroller.cpp \
    ../../quipchat/qtsparkle/src/updatechecker.cpp \
    ../../quipchat/qtsparkle/src/updatedialog.cpp \
    ../../quipchat/qtsparkle/src/updater.cpp

OTHER_FILES += \
    ../../quipchat/qtsparkle/src/translations.ts
