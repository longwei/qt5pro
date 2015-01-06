QT += widgets

HEADERS += \
    widget.h \
    idlewatch.h

SOURCES += \
    main.cpp \
    widget.cpp \
    idlewatch.cpp

include(../../../externals.pri)

unix {
    INCLUDEPATH += $$KIDLETIME_INCLUDES

    LIBS += $$KIDLETIME_LIBS
}

include(../app.pri)
