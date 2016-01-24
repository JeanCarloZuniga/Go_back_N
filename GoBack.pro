#-------------------------------------------------
#
# Project created by QtCreator 2016-01-24T14:46:51
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoBack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    servidor.cpp \
    cliente.cpp \
    intermediario.cpp

HEADERS  += mainwindow.h \
    servidor.h \
    cliente.h \
    intermediario.h

FORMS    += mainwindow.ui
