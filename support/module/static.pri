TEMPLATE = lib
CONFIG  += staticlib

unix {
    DESTDIR = ../../lib
}
win32 {
    DESTDIR = ..\\..\\lib
}

unix {
    QMAKE_CLEAN *= $$DESTDIR/*$$TARGET*
}
win32 {
    QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
}

include(../common.pri)
