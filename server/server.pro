#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T20:47:21
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += c++11
# c++11 support form mac os
macx:QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
macx:LIBS += -stdlib=libc++ -mmacosx-version-min=10.7


INCLUDEPATH += ../boost_1_53_0
LIBS += -L../boost_1_53_0/stage/lib

win32:LIBS += -lboost_system-mgw47-mt-sd-1_53 -lws2_32 -lmswsock
macx:LIBS += -lboost_system

INCLUDEPATH += ../common
INCLUDEPATH += ../json

TEMPLATE = app


SOURCES += main.cpp \
    thread_pool.cpp \
    session.cpp \
    server.cpp \
    ../common/logger.cpp

HEADERS += \
    thread_pool.hpp \
    session.hpp \
    server_defs.hpp \
    server.hpp \
    match.hpp \
    game_object.hpp \
    field.hpp \
    ../common/subsystem.hpp \
    ../common/primitives.hpp \
    ../common/noncopyable.hpp \
    ../common/master.hpp \
    ../common/logger.hpp \
    ../common/cpp_defs.hpp \
    ../common/common_defs.hpp \
    user_info.hpp
