#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T16:40:34
#
#-------------------------------------------------

QT       -= gui

TARGET = Interface
TEMPLATE = lib

DEFINES += INTERFACE_LIBRARY

SOURCES +=

HEADERS +=\
        interface_global.h \
    Data.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
