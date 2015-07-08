#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T20:24:05
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    staticdo.cpp

HEADERS  += mainwindow.h \
    staticdo.h \
    Inc/bdaqctrl.h

FORMS += \
    staticdo.ui
