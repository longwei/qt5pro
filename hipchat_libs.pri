LIBS += -L../bin

LIBS += -lsimplecrypt -lqtsparkle -lqtjson -lcommon -lqxmpp -lqtwidget -lqtsingleapplication -lcanberra -lbreakpad
LIBS += -lShell32 -lAdvapi32 -lWinmm

LIBS += -L$$EXTERNALS_BUILD_DIR/qwebchannel/lib -lQt5WebChannel
LIBS += -L$$EXTERNALS_BUILD_DIR/sonnet/lib -lKF5SonnetUi -lKF5SonnetCore
LIBS += -L../../externals/bin -llibhunspell

win32 {
    LIBS += -L../../quipchat/addlive/win32 -ladl_sdk -lyuv
    QMAKE_LFLAGS += /NODEFAULTLIB:libcmt
}

win32 {
    QMAKE_POST_LINK += $$quote(copy $$EXTERNALS_BUILD_DIR_WIN\sonnet\bin\*.dll ..\bin)
    QMAKE_POST_LINK += $$quote(&& copy ..\..\quipchat\addlive\win32\*.dll ..\bin)
}

win32 {
    PRE_TARGETDEPS += ../bin/qtwidget.lib
    PRE_TARGETDEPS += ../bin/common.lib
    PRE_TARGETDEPS += ../bin/qxmpp.lib
}
