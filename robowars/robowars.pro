#-------------------------------------------------
#
# Project created by QtCreator 2013-03-31T12:43:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


TARGET = robowars
TEMPLATE = app

INCLUDEPATH += ../boost_1_53_0
LIBS += -L../boost_1_53_0/stage/lib

win32:LIBS += -lboost_system-mgw47-mt-sd-1_53 -lws2_32 -lmswsock
macx:LIBS += -lboost_system

# c++11 support form mac os
macx:QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
macx:LIBS += -stdlib=libc++ -mmacosx-version-min=10.7

SOURCES += \
    client/mainwindow.cpp \
    \
    server/session.cpp \
    server/server.cpp \
    \
    main.cpp \
    logger.cpp \
    client/client_entry_point.cpp \
    server/server_entry_point.cpp \
    server/thread_pool.cpp

HEADERS  += \
    client/mainwindow.h \
    client/client_defs.hpp \
    \
    server/thread_pool.hpp \
    server/session.hpp \
    server/server.hpp \
    server/logger.hpp \
    server/server_defs.hpp \
    \
    subsystem.hpp \
    noncopyable.hpp \
    cpp_defs.hpp \
    master.hpp \
    logger.hpp \
    shutdown_flag.hpp

FORMS    += client/mainwindow.ui

OTHER_FILES +=
