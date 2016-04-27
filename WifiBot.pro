#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T11:43:08
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkitwidgets
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WifiBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connexion.cpp \
    roues.cpp \
    camera.cpp \
    capteur.cpp

HEADERS  += mainwindow.h \
    connexion.h \
    roues.h \
    camera.h \
    capteur.h

FORMS    += mainwindow.ui

DISTFILES += \
    ar_patts/01.pdf \
    ar_patts/02.pdf \
    ar_patts/03.pdf \
    ar_patts/04.pdf \
    ar_patts/05.pdf \
    ar_patts/06.pdf \
    ar_patts/07.pdf \
    ar_patts/08.pdf \
    ar_patts/09.pdf \
    ar_patts/10.pdf \
    ar_patts/cent.pdf \
    ar_patts/dollar.pdf \
    ar_patts/environment.pdf
