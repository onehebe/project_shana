#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T13:59:00
#
#-------------------------------------------------

QT       += widgets       \
            printsupport

TARGET = qcustomplot
TEMPLATE = lib

DEFINES += QCUSTOMPLOT_LIBRARY

SOURCES += qcustomplot.cpp

HEADERS += qcustomplot.h\
        qcustomplot_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
