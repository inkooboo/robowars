#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T20:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

CONFIG += c++11
# c++11 support form mac os
macx:QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
macx:LIBS += -stdlib=libc++ -mmacosx-version-min=10.7

INCLUDEPATH += ../common
INCLUDEPATH += ../json

SOURCES += main.cpp\
        mainwindow.cpp \
    ../common/logger.cpp

HEADERS  += mainwindow.h \
    ../common/subsystem.hpp \
    ../common/primitives.hpp \
    ../common/noncopyable.hpp \
    ../common/master.hpp \
    ../common/logger.hpp \
    ../common/cpp_defs.hpp \
    ../common/common_defs.hpp

FORMS    += mainwindow.ui
