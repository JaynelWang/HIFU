#-------------------------------------------------
#
# Project created by QtCreator 2015-07-19T20:15:19
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DO
INCLUDEPATH += "./PhaseInfo"
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    staticdo.cpp \
    PhaseInfo/abs.c \
    PhaseInfo/angle.c \
    PhaseInfo/ArrayDiv.c \
    PhaseInfo/colon.c \
    PhaseInfo/cos.c \
    PhaseInfo/exp.c \
    PhaseInfo/fliplr.c \
    PhaseInfo/flipud.c \
    PhaseInfo/ForwardMatrix.c \
    PhaseInfo/getArrayInfo.c \
    PhaseInfo/getFocusInfo.c \
    PhaseInfo/PhaseInfo.c \
    PhaseInfo/PhaseInfo_emxutil.c \
    PhaseInfo/PhaseInfo_initialize.c \
    PhaseInfo/PhaseInfo_rtwutil.c \
    PhaseInfo/PhaseInfo_terminate.c \
    PhaseInfo/PsuedoInverse.c \
    PhaseInfo/rdivide.c \
    PhaseInfo/repmat.c \
    PhaseInfo/round.c \
    PhaseInfo/rt_nonfinite.c \
    PhaseInfo/rtGetInf.c \
    PhaseInfo/rtGetNaN.c \
    PhaseInfo/sin.c \
    PhaseInfo/sum.c \
    docontroller.cpp

HEADERS  += mainwindow.h \
    staticdo.h \
    Inc/bdaqctrl.h \
    PhaseInfo/abs.h \
    PhaseInfo/angle.h \
    PhaseInfo/ArrayDiv.h \
    PhaseInfo/colon.h \
    PhaseInfo/cos.h \
    PhaseInfo/exp.h \
    PhaseInfo/fliplr.h \
    PhaseInfo/flipud.h \
    PhaseInfo/ForwardMatrix.h \
    PhaseInfo/getArrayInfo.h \
    PhaseInfo/getFocusInfo.h \
    PhaseInfo/PhaseInfo.h \
    PhaseInfo/PhaseInfo_emxutil.h \
    PhaseInfo/PhaseInfo_initialize.h \
    PhaseInfo/PhaseInfo_rtwutil.h \
    PhaseInfo/PhaseInfo_terminate.h \
    PhaseInfo/PhaseInfo_types.h \
    PhaseInfo/PsuedoInverse.h \
    PhaseInfo/rdivide.h \
    PhaseInfo/repmat.h \
    PhaseInfo/round.h \
    PhaseInfo/rt_defines.h \
    PhaseInfo/rt_nonfinite.h \
    PhaseInfo/rtGetInf.h \
    PhaseInfo/rtGetNaN.h \
    PhaseInfo/rtwtypes.h \
    PhaseInfo/sin.h \
    PhaseInfo/sum.h \
    definition.h \
    docontroller.h
