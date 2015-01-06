QT += widgets

CONFIG += C++11

SOURCES += \
    main.cpp \
    widget.cpp \
    textedit.cpp

HEADERS += \
    widget.h \
    textedit.h

include(../app.pri)

win32 {
    DEFINES -= UNICODE
}
