#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T16:54:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PA
INCLUDEPATH += "./SerialPortController"
TEMPLATE = app


SOURCES += main.cpp\
    poweramp.cpp \
    mainwindow.cpp \
    SerialPortController/serialportcontroller.cpp

HEADERS  += \
    poweramp.h \
    mainwindow.h \
    SerialPortController/serialportcontroller.h

FORMS += \
    mainwindow.ui
