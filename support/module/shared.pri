TEMPLATE = lib

win32 {
    CONFIG += dll
}

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

include(../common.pri)
