TEMPLATE = lib

CONFIG += staticlib

TARGET = breakpad

DESTDIR = ../bin

DEFINES += UNICODE

HEADERS += \
    ../../quipchat/breakpad-qt/BreakpadHandler.h

SOURCES += \
    ../../quipchat/breakpad-qt/BreakpadHandler.cpp \
    ../../quipchat/google-breakpad/src/common/windows/guid_string.cc \
    ../../quipchat/google-breakpad/src/common/windows/string_utils.cc \
    ../../quipchat/google-breakpad/src/client/windows/crash_generation/client_info.cc \
    ../../quipchat/google-breakpad/src/client/windows/crash_generation/crash_generation_client.cc \
    ../../quipchat/google-breakpad/src/client/windows/crash_generation/crash_generation_server.cc \
    ../../quipchat/google-breakpad/src/client/windows/crash_generation/minidump_generator.cc \
    ../../quipchat/google-breakpad/src/client/windows/handler/exception_handler.cc

INCLUDEPATH += ../../quipchat/google-breakpad/src
INCLUDEPATH += ../../quipchat/common

INCLUDEPATH += ../../qxmpp/src/client
INCLUDEPATH += ../../qxmpp/src/base

LIBS += -L../bin
LIBS += -lxmpp
