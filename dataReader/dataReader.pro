#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T13:51:47
#
#-------------------------------------------------

QT       += scripttools \
            script

QT       -= core gui

TARGET = dataReader
TEMPLATE = lib

DEFINES += DATAREADER_LIBRARY

SOURCES += datareader.cpp \
    data.cpp

HEADERS += datareader.h\
        datareader_global.h \
    data.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG  += c++11
