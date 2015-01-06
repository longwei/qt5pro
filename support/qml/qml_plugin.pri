TEMPLATE = lib

win32 {
    CONFIG += dll
}

CONFIG  += qt plugin
QT      += qml quick widgets

unix {
    DESTDIR = ../../bin
}
win32 {
    DLLDESTDIR = ..\\..\\bin
    DESTDIR = ..\\..\\lib
}

unix {
    QMAKE_CLEAN *= $$DESTDIR/*$$TARGET*
}
win32 {
    QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
    QMAKE_CLEAN *= $$DLLDESTDIR\\*$$TARGET*
}

unix {
    DOLLAR = $
    QUOTE = "'"

    QMAKE_LFLAGS += -Wl,-rpath,$${QUOTE}$${DOLLAR}$${DOLLAR}ORIGIN$${QUOTE}
    QMAKE_LFLAGS += -Wl,-z,origin
}

include(../common.pri)

OTHER_FILES += \
    ../ProjectPlanner/test.qml

