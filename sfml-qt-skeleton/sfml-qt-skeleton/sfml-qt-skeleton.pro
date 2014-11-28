#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T12:21:55
#
#-------------------------------------------------

QT       += core gui
#QT       += x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/home/john/Documents/cpp/qt2/SFML/build/lib -lsfml-graphics -lsfml-window -lsfml-system
LIBS += -L/usr/include/X11 -lX11

TARGET = sfml-qt-skeleton
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qsfmlcanvas.cpp \
    mycanvas.cpp

HEADERS  += mainwindow.h \
    qsfmlcanvas.h \
    mycanvas.h

FORMS    += mainwindow.ui
