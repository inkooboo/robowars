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
LIBS += -L../boost_1_53_0/stage/lib -lboost_system

# c++11 support form mac os
macx:QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
macx:LIBS += -stdlib=libc++ -mmacosx-version-min=10.7

SOURCES += \
    client/mainwindow.cpp \
    client/client_main.cpp \
    \
    server/session.cpp \
    server/server.cpp \
    server/logger.cpp \
    \
    main.cpp \
    server/server_main.cpp

HEADERS  += \
    client/mainwindow.h \
    \
    server/thread_pool.hpp \
    server/session.hpp \
    server/server.hpp \
    server/logger.hpp \
    subsystem.hpp \
    noncopyable.hpp \
    master.hpp \
    cpp11.hpp

FORMS    += client/mainwindow.ui

OTHER_FILES += \
    server/config.txt
