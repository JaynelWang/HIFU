#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T13:49:24
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialportcontroller.cpp \
    poweramp.cpp

HEADERS  += mainwindow.h \
    serialportcontroller.h \
    poweramp.h

FORMS    += mainwindow.ui
