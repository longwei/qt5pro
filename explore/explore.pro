QT += gui network xml widgets quick webkit webkitwidgets opengl

unix {
    QT += x11extras
}

win32 {
    TEMPLATE = app
}
unix {
    TEMPLATE = lib
    CONFIG += staticlib
}

TARGET = explore

unix {
    DESTDIR = ../bin
}
win32 {
    DESTDIR = ..\\bin
}

SOURCES += \
    main.cpp

include(../hipchat_includes.pri)
include(../hipchat_libs.pri)

include(../qt5pro.pri)
