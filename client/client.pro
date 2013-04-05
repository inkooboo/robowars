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
INCLUDEPATH += ..

SOURCES += main.cpp\
        mainwindow.cpp \
    ../common/logger.cpp \
    ../json/json_writer.cpp \
    ../json/json_valueiterator.inl \
    ../json/json_value.cpp \
    ../json/json_reader.cpp \
    ../json/json_internalmap.inl \
    ../json/json_internalarray.inl

HEADERS  += mainwindow.h \
    ../common/subsystem.hpp \
    ../common/primitives.hpp \
    ../common/noncopyable.hpp \
    ../common/master.hpp \
    ../common/logger.hpp \
    ../common/cpp_defs.hpp \
    ../common/common_defs.hpp \
    ../json/writer.h \
    ../json/value.h \
    ../json/reader.h \
    ../json/json.h \
    ../json/json_tool.h \
    ../json/json_batchallocator.h \
    ../json/forwards.h \
    ../json/features.h \
    ../json/config.h \
    ../json/autolink.h

FORMS    += mainwindow.ui
