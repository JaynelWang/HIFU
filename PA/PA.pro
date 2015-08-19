#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T09:58:43
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PA
TEMPLATE = app

INCLUDEPATH += ../lib
LIBS += ../bin/PowerAmp.dll

SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
