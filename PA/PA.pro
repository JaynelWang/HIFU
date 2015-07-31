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


SOURCES += main.cpp\
        mainwindow.cpp \
    poweramp.cpp

HEADERS  += mainwindow.h \
    poweramp.h

FORMS    += mainwindow.ui
