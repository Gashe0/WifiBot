#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T11:43:08
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WifiBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connexion.cpp

HEADERS  += mainwindow.h \
    connexion.h

FORMS    += mainwindow.ui
