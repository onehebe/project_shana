#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T13:24:43
#
#-------------------------------------------------

QT       += core gui \
            printsupport script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataAnalyser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ivcurve.cpp \
    dataanalyser.cpp \
    layoutdesigner.cpp \
    databasemanager.cpp

HEADERS  += mainwindow.h \
    ivcurve.h \
    dataanalyser.h \
    layoutdesigner.h \
    databasemanager.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../dataReader/release/ -ldataReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../dataReader/debug/ -ldataReader
else:unix: LIBS += -L$$OUT_PWD/../dataReader/ -ldataReader

INCLUDEPATH += $$PWD/../dataReader
DEPENDPATH += $$PWD/../dataReader

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/release/ -lqcustomplot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/debug/ -lqcustomplot
else:unix: LIBS += -L$$OUT_PWD/../qcustomplot/ -lqcustomplot

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

OTHER_FILES += \
    config/interpreter.js
