TEMPLATE = app

QT += testlib
#QT -= gui

CONFIG   += console

unix {
    DESTDIR = ../../bin
}
win32 {
    DESTDIR = ..\\..\\bin
}

unix {
    QMAKE_CLEAN *= $$DESTDIR/*$$TARGET*
}
win32 {
    QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
}

unix {
    DOLLAR = $
    QUOTE = "'"

    QMAKE_LFLAGS += -Wl,-rpath,$${QUOTE}$${DOLLAR}$${DOLLAR}ORIGIN$${QUOTE}
    QMAKE_LFLAGS += -Wl,-z,origin
}

include(../common.pri)
