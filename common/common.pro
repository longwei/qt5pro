QT += qml network xml

TEMPLATE = lib

CONFIG += staticlib
CONFIG += C++11

TARGET = common

DESTDIR = ../bin

HEADERS += \
    ../../quipchat/common/conversations/ChatRoom.h \
    ../../quipchat/common/conversations/ChatRoomModel.h \
    ../../quipchat/common/conversations/Conversation.h \
    ../../quipchat/common/conversations/ConversationView.h \
    ../../quipchat/common/conversations/HipChatHistoryRequestIq.h \
    ../../quipchat/common/conversations/MessageParser.h \
    ../../quipchat/common/conversations/OneToOne.h \
    ../../quipchat/common/conversations/OneToOneManager.h \
    ../../quipchat/common/conversations/TabModel.h \
    ../../quipchat/common/roomnrostermodels/AutoCompleteSortProxyModel.h \
    ../../quipchat/common/roomnrostermodels/JoinModel.h \
    ../../quipchat/common/roomnrostermodels/ParticipantsModel.h \
    ../../quipchat/common/roomnrostermodels/RoomListModel.h \
    ../../quipchat/common/roomnrostermodels/RosterModel.h \
    ../../quipchat/common/roomnrostermodels/SidebarModel.h \
    ../../quipchat/common/roomnrostermodels/SidebarModelFactory.h \
    ../../quipchat/common/roomnrostermodels/SortedStringListModel.h \
    ../../quipchat/common/roomnrostermodels/SpecialMentionNameModel.h \
    ../../quipchat/common/roomnrostermodels/TabCompleteSortProxyModel.h \
    ../../quipchat/common/AddLiveController.h \
    ../../quipchat/common/AddLiveController_p.h \
    ../../quipchat/common/AddLiveInterface.h \
    ../../quipchat/common/AddLiveIq.h \
    ../../quipchat/common/AdlUtils.h \
    ../../quipchat/common/ConnectivityManager.h \
    ../../quipchat/common/HipHttpApi.h \
    ../../quipchat/common/NoFileNetworkAccessManager.h \
#    ../../quipchat/common/OnlineStatusNLM.h \
    ../../quipchat/common/ProfileManager.h \
    ../../quipchat/common/ServerConnection.h \
    ../../quipchat/common/Settings.h \
    ../../quipchat/common/Utils.h

SOURCES += \
    ../../quipchat/common/conversations/ChatRoom.cpp \
    ../../quipchat/common/conversations/ChatRoomModel.cpp \
    ../../quipchat/common/conversations/Conversation.cpp \
    ../../quipchat/common/conversations/HipChatHistoryRequestIq.cpp \
    ../../quipchat/common/conversations/MessageParser.cpp \
    ../../quipchat/common/conversations/OneToOne.cpp \
    ../../quipchat/common/conversations/OneToOneManager.cpp \
    ../../quipchat/common/conversations/TabModel.cpp \
    ../../quipchat/common/roomnrostermodels/AutoCompleteSortProxyModel.cpp \
    ../../quipchat/common/roomnrostermodels/JoinModel.cpp \
    ../../quipchat/common/roomnrostermodels/ParticipantsModel.cpp \
    ../../quipchat/common/roomnrostermodels/RoomListModel.cpp \
    ../../quipchat/common/roomnrostermodels/RosterModel.cpp \
    ../../quipchat/common/roomnrostermodels/SidebarModel.cpp \
    ../../quipchat/common/roomnrostermodels/SidebarModelFactory.cpp \
    ../../quipchat/common/roomnrostermodels/SortedStringListModel.cpp \
    ../../quipchat/common/roomnrostermodels/SpecialMentionNameModel.cpp \
    ../../quipchat/common/roomnrostermodels/TabCompleteSortProxyModel.cpp \
    ../../quipchat/common/AddLiveController.cpp \
    ../../quipchat/common/AddLiveIq.cpp \
    ../../quipchat/common/ConnectivityManager.cpp \
    ../../quipchat/common/HipHttpApi.cpp \
    ../../quipchat/common/NoFileNetworkAccessManager.cpp \
#    ../../quipchat/common/OnlineStatusNLM.cpp \
    ../../quipchat/common/ProfileManager.cpp \
    ../../quipchat/common/ServerConnection.cpp \
    ../../quipchat/common/Settings.cpp \
    ../../quipchat/common/Utils.cpp

OTHER_FILES += \
    ../../quipchat/common/conversations/chat.js \
    ../../quipchat/common/conversations/chat.css

INCLUDEPATH += ../../quipchat/common/conversations
INCLUDEPATH += ../../quipchat/common/roomnrostermodels

INCLUDEPATH += ../../quipchat/common

INCLUDEPATH += ../../quipchat/qt-json
INCLUDEPATH += ../../quipchat/SimpleCrypt

INCLUDEPATH += ../../qxmpp/src/client
INCLUDEPATH += ../../qxmpp/src/base

win32 {
    QMAKE_CXXFLAGS += /Zc:wchar_t
}

include(../addlive.pri)

include(../qt5pro.pri)
