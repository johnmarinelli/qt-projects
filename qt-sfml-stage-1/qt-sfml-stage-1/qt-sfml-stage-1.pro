#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T00:13:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/home/john/Documents/cpp/qt2/SFML/build/lib -lsfml-graphics -lsfml-window -lsfml-system
LIBS += -L/usr/include/X11 -lX11

TARGET = qt-smfl-stage-1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qsfmlcanvas.cpp \
    mycanvas.cpp

HEADERS  += mainwindow.h \
    qsfmlcanvas.h \
    mycanvas.h

FORMS    += mainwindow.ui

RESOURCES += \
    tiles.qrc
