QT += network widgets

TEMPLATE = lib
CONFIG += staticlib

#DEFINES += QT_QTSINGLEAPPLICATION_EXPORT
#DEFINES += QT_QTLOCKEDFILE_EXPORT

DESTDIR = ../bin

win32 {
    HEADERS += \
        ../../quipchat/qtsingleapplication/src/qtlocalpeer.h \
        ../../quipchat/qtsingleapplication/src/qtlockedfile.h \
        ../../quipchat/qtsingleapplication/src/qtsingleapplication.h \
        ../../quipchat/qtsingleapplication/src/qtsinglecoreapplication.h

    SOURCES += \
        ../../quipchat/qtsingleapplication/src/qtlocalpeer.cpp \
        ../../quipchat/qtsingleapplication/src/qtlockedfile.cpp \
        ../../quipchat/qtsingleapplication/src/qtlockedfile_win.cpp \
        ../../quipchat/qtsingleapplication/src/qtsingleapplication.cpp \
        ../../quipchat/qtsingleapplication/src/qtsinglecoreapplication.cpp
}
