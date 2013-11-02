#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T17:08:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quadclient
TEMPLATE = app

LIBS += "C:\SDL\SDL-1.2.15\bin\SDL.dll"

INCLUDEPATH += "C:\SDL\SDL-1.2.15\include\SDL"

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
