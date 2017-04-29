#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T20:09:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    state.cpp \
    basis.cpp

HEADERS  += mainwindow.h \
    state.h \
    basis.h

FORMS    += mainwindow.ui

RC_FILE = spin.rc
