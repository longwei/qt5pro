QT += gui network xml widgets quick webkit webkitwidgets opengl

unix {
    QT += x11extras
}

#TEMPLATE = app
TEMPLATE = lib

CONFIG += staticlib
CONFIG += C++11

unix {
    DESTDIR = ../bin
}
win32 {
    DESTDIR = ..\\bin
}

HEADERS += \
    ../../quipchat/qtwidget/dialogs/AboutDialog.h \
    ../../quipchat/qtwidget/dialogs/CreateRoomDialog.h \
    ../../quipchat/qtwidget/dialogs/InviteDialog.h \
    ../../quipchat/qtwidget/dialogs/JoinRoomDialog.h \
    ../../quipchat/qtwidget/dialogs/ProxyConfigWidget.h \
    ../../quipchat/qtwidget/dialogs/SettingsDialog.h \
    ../../quipchat/qtwidget/AddLiveQuickItem.h \
    ../../quipchat/qtwidget/CallManager.h \
    ../../quipchat/qtwidget/CallNotificationWindow.h \
    ../../quipchat/qtwidget/CallWindow.h \
    ../../quipchat/qtwidget/HipLogin.h \
    ../../quipchat/qtwidget/HipMainWindow.h \
    ../../quipchat/qtwidget/HipTextHelper.h \
    ../../quipchat/qtwidget/Lobby.h \
    ../../quipchat/qtwidget/LoggingCategories.h \
    ../../quipchat/qtwidget/OSDManager.h \
    ../../quipchat/qtwidget/OSDView.h \
    ../../quipchat/qtwidget/PresenceWidget.h \
    ../../quipchat/qtwidget/SystemTray.h \
    ../../quipchat/qtwidget/versioninfo.rc.in \
    ../../quipchat/qtwidget/tabcontent/ChatInput/ChatTextInput.h \
    ../../quipchat/qtwidget/tabcontent/ChatInput/EmoticonSyntaxHighligher.h \
    ../../quipchat/qtwidget/tabcontent/ChatInput/EmoticonTextEdit.h \
    ../../quipchat/qtwidget/tabcontent/ChatInput/RemoteImageCache.h \
#    ../../quipchat/qtwidget/tabcontent/ChatQmlView.h \
    ../../quipchat/qtwidget/tabcontent/ChatView.h \
    ../../quipchat/qtwidget/tabcontent/ChatWebView.h \
    ../../quipchat/qtwidget/tabcontent/EmoticonSelector.h \
    ../../quipchat/qtwidget/tabcontent/FileNameEditor.h \
    ../../quipchat/qtwidget/tabcontent/HipWebView.h \
    ../../quipchat/qtwidget/tabcontent/NickCompleter.h \
    ../../quipchat/qtwidget/tabcontent/OneOnOneView.h \
    ../../quipchat/qtwidget/tabcontent/RichTextDelegate.h \
    ../../quipchat/qtwidget/tabcontent/RosterListView.h \
    ../../quipchat/qtwidget/tabcontent/SearchPopup.h \
    ../../quipchat/qtwidget/tabcontent/SearchResultConversation.h \
    ../../quipchat/qtwidget/tabcontent/SearchResultsView.h \
    ../../quipchat/qtwidget/tabcontent/Sidebar.h \
    ../../quipchat/qtwidget/tabcontent/TabContent.h \
    ../../quipchat/qtwidget/tabcontent/TopicWidget.h \
    ../../quipchat/qtwidget/tabcontent/UploadProgressBar.h \
    ../../quipchat/qtwidget/tabcontent/WebView.h \
    ../../quipchat/qtwidget/IdleTime.h \
    ../../quipchat/qtwidget/QuickWindowContainer.h \
    ../../quipchat/qtwidget/ScreenWatch.h

SOURCES += \
    ../../quipchat/qtwidget/dialogs/AboutDialog.cpp \
    ../../quipchat/qtwidget/dialogs/CreateRoomDialog.cpp \
    ../../quipchat/qtwidget/dialogs/InviteDialog.cpp \
    ../../quipchat/qtwidget/dialogs/JoinRoomDialog.cpp \
    ../../quipchat/qtwidget/dialogs/ProxyConfigWidget.cpp \
    ../../quipchat/qtwidget/dialogs/SettingsDialog.cpp \
    ../../quipchat/qtwidget/AddLiveQuickItem.cpp \
    ../../quipchat/qtwidget/CallManager.cpp \
    ../../quipchat/qtwidget/CallNotificationWindow.cpp \
    ../../quipchat/qtwidget/CallWindow.cpp \
    ../../quipchat/qtwidget/HipLogin.cpp \
    ../../quipchat/qtwidget/HipMainWindow.cpp \
    ../../quipchat/qtwidget/HipTextHelper.cpp \
    ../../quipchat/qtwidget/Lobby.cpp \
#    ../../quipchat/qtwidget/main.cpp \
    ../../quipchat/qtwidget/OSDManager.cpp \
    ../../quipchat/qtwidget/OSDView.cpp \
    ../../quipchat/qtwidget/PresenceWidget.cpp \
    ../../quipchat/qtwidget/SystemTray.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatInput/ChatTextInput.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatInput/EmoticonSyntaxHighligher.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatInput/EmoticonTextEdit.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatInput/RemoteImageCache.cpp \
#    ../../quipchat/qtwidget/tabcontent/ChatQmlView.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatView.cpp \
    ../../quipchat/qtwidget/tabcontent/ChatWebView.cpp \
    ../../quipchat/qtwidget/tabcontent/EmoticonSelector.cpp \
    ../../quipchat/qtwidget/tabcontent/FileNameEditor.cpp \
    ../../quipchat/qtwidget/tabcontent/HipWebView.cpp \
    ../../quipchat/qtwidget/tabcontent/NickCompleter.cpp \
    ../../quipchat/qtwidget/tabcontent/OneOnOneView.cpp \
    ../../quipchat/qtwidget/tabcontent/RichTextDelegate.cpp \
    ../../quipchat/qtwidget/tabcontent/RosterListView.cpp \
    ../../quipchat/qtwidget/tabcontent/SearchPopup.cpp \
    ../../quipchat/qtwidget/tabcontent/SearchResultConversation.cpp \
    ../../quipchat/qtwidget/tabcontent/SearchResultsView.cpp \
    ../../quipchat/qtwidget/tabcontent/Sidebar.cpp \
    ../../quipchat/qtwidget/tabcontent/TabContent.cpp \
    ../../quipchat/qtwidget/tabcontent/TopicWidget.cpp \
    ../../quipchat/qtwidget/tabcontent/UploadProgressBar.cpp \
    ../../quipchat/qtwidget/tabcontent/WebView.cpp \
    ../../quipchat/qtwidget/IdleTime.cpp \
    ../../quipchat/qtwidget/QuickWindowContainer.cpp \
    ../../quipchat/qtwidget/ScreenWatch.cpp

#win32 {
#SOURCES += ../../quipchat/qtwidget/main.cpp
#}

FORMS += \
    ../../quipchat/qtwidget/dialogs/aboutDialog.ui \
    ../../quipchat/qtwidget/dialogs/changePrivacyDialog.ui \
    ../../quipchat/qtwidget/dialogs/CreateRoomDialog.ui \
    ../../quipchat/qtwidget/dialogs/inviteDialog.ui \
    ../../quipchat/qtwidget/dialogs/loginDialog.ui \
    ../../quipchat/qtwidget/dialogs/logViewer.ui \
    ../../quipchat/qtwidget/dialogs/ProxyConfigWidget.ui \
    ../../quipchat/qtwidget/dialogs/settingsDialog.ui \
    ../../quipchat/qtwidget/tabcontent/oneToOneSidebar.ui

OTHER_FILES += \
    ../../quipchat/qtwidget/dialogs/LoginAnimation.qml \
    ../../quipchat/qtwidget/qml/CallActionButton.qml \
    ../../quipchat/qtwidget/qml/CallNotificationWindow.qml \
    ../../quipchat/qtwidget/qml/CallStatus.qml \
    ../../quipchat/qtwidget/qml/CallWindow.qml \
    ../../quipchat/qtwidget/qml/ChannelListView.qml \
    ../../quipchat/qtwidget/qml/ConversationView.qml \
    ../../quipchat/qtwidget/qml/FM.qml \
    ../../quipchat/qtwidget/qml/HipScrollViewStyle.qml \
    ../../quipchat/qtwidget/qml/HipText.qml \
    ../../quipchat/qtwidget/qml/IndefiniteProgressBar.qml \
    ../../quipchat/qtwidget/qml/OSDView.qml \
    ../../quipchat/qtwidget/qml/PreviewWindow.qml \
    ../../quipchat/qtwidget/qml/ScreenShareDialog.qml \
    ../../quipchat/qtwidget/qml/SettingsLocalVideo.qml \
    ../../quipchat/qtwidget/qml/StarRating.qml \
    ../../quipchat/qtwidget/qml/TabView.qml \
    ../../quipchat/qtwidget/qml/Toolbar.qml \
    ../../quipchat/qtwidget/qml/ToolButton.qml \
    ../../quipchat/qtwidget/qml/qmldir \
    ../../quipchat/qtwidget/callNotificationWindow.json \
    ../../quipchat/qtwidget/debianSymbolStore.rb \
    ../../quipchat/qtwidget/hipchat.sh \
    ../../quipchat/qtwidget/linuxbrowserlaunch.sh \
    ../../quipchat/qtwidget/hipchat.css \
    ../../quipchat/qtwidget/hipchat.rc

include(../hipchat_includes.pri)

include(../qt5pro.pri)
