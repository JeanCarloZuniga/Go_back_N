#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T22:27:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cliente.cpp \
    servidor.cpp

HEADERS  += mainwindow.h \
    cliente.h \
    servidor.h

FORMS    += mainwindow.ui
