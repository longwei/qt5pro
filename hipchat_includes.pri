win32 {
    RESOURCES += ../../quipchat/web.qrc \
        ../../quipchat/google-code-prettify/prettify.qrc \
        ../../quipchat/certs/certs.qrc \
        ../../quipchat/licenses/licenses.qrc
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

include(addlive.pri)

include(externals.pri)

INCLUDEPATH += $$EXTERNALS_BUILD_DIR/sonnet/include/KF5/SonnetUi
INCLUDEPATH += $$EXTERNALS_BUILD_DIR/sonnet/include/KF5/SonnetCore

unix {
    INCLUDEPATH += $$EXTERNALS_BUILD_DIR/kwindowsystem/include/KF5/KWindowSystem
    INCLUDEPATH += ../../quipchat/google-breakpad/src/
    INCLUDEPATH += ../../quipchat/kdelibs/knotifications/src/
    INCLUDEPATH += ../../quipchat/kdelibs
    INCLUDEPATH += ../kdelibs/src_copy
}
