QT += testlib xml network qml

TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    ../../quipchat/tests/unittests/TestCommonUtils.h \
    ../../quipchat/tests/unittests/Conversation/TestToXMLCharacterRange.h

SOURCES += \
    ../../quipchat/tests/unittests/TestAddLiveController.cpp \
    ../../quipchat/tests/unittests/TestCommonUtils.cpp \
    ../../quipchat/tests/unittests/TestOneToOneXHTML.cpp \
    ../../quipchat/tests/unittests/Conversation/TestToXMLCharacterRange.cpp

unix {
    HEADERS += \
        ../../quipchat/tests/unittests/sound_mock_control.h

    SOURCES += \
        ../../quipchat/tests/unittests/sound_mock.cpp \
        ../../quipchat/tests/unittests/addlive_mock.cpp
        ../../quipchat/tests/unittests/TestSoundNotification.cpp
}

INCLUDEPATH += ../../quipchat/qtwidget
INCLUDEPATH += ../../quipchat/qtwidget/dialogs
INCLUDEPATH += ../../quipchat/qtwidget/tabcontent
INCLUDEPATH += ../../quipchat/qtwidget/tabcontent/ChatInput

INCLUDEPATH += ../../quipchat/common
INCLUDEPATH += ../../quipchat/common/conversations
INCLUDEPATH += ../../quipchat/common/roomnrostermodels

INCLUDEPATH += ../../qxmpp/src/client
INCLUDEPATH += ../../qxmpp/src/base

INCLUDEPATH += ../../quipchat/canberra

INCLUDEPATH += ../../quipchat/qtsingleapplication/src

INCLUDEPATH += ../../quipchat/qtsparkle/src

unix {
    INCLUDEPATH += ../../quipchat/dbus-scripting
}

include(../addlive.pri)

include(../externals.pri)

INCLUDEPATH += $$EXTERNALS_BUILD_DIR/sonnet/include/KF5/SonnetUi
INCLUDEPATH += $$EXTERNALS_BUILD_DIR/sonnet/include/KF5/SonnetCore

INCLUDEPATH += $$EXTERNALS_BUILD_DIR/kidletime/include/KF5/KIdleTime

unix {
    INCLUDEPATH += $$EXTERNALS_BUILD_DIR/kwindowsystem/include/KF5/KWindowSystem
    INCLUDEPATH += ../../quipchat/google-breakpad/src/
    INCLUDEPATH += ../../quipchat/kdelibs/knotifications/src/
    INCLUDEPATH += ../../quipchat/kdelibs
    INCLUDEPATH += ../kdelibs/src_copy
}

include(../qt5pro.pri)
