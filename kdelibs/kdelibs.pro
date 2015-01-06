QT += widgets dbus

TEMPLATE = lib

CONFIG += staticlib

TARGET = kdelibs

DESTDIR = ../bin

OTHER_FILES += \
    ../../quipchat/kdelibs/MinimizeRestore.h \
    src_copy/statusnotifierwatcher_interface.h \
    src_copy/statusnotifieritemadaptor.h \
    src_copy/notifications_interface.h \
    src_copy/knotify_interface.h \
    src_copy/knotifications_export.h \
    src_copy/config-knotifications.h \
    ../../quipchat/kdelibs/knotifications/src/kstatusnotifieritemprivate_p.h \
    ../../quipchat/kdelibs/knotifications/src/kstatusnotifieritemdbus_p.h \
    ../../quipchat/kdelibs/knotifications/src/kstatusnotifieritem.h \
    ../../quipchat/kdelibs/knotifications/src/knotificationrestrictions.h \
    ../../quipchat/kdelibs/knotifications/src/knotificationmanager_p.h \
    ../../quipchat/kdelibs/knotifications/src/knotification.h

SOURCES += \
    ../../quipchat/kdelibs/MinimizeRestore.cpp

include(../externals.pri)

INCLUDEPATH += $$EXTERNALS_BUILD_DIR/kwindowsystem/include/KF5/KWindowSystem
INCLUDEPATH += ../../quipchat/kdelibs/knotifications/src
INCLUDEPATH += src_copy
