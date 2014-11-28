#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qDebug("hello");
    w.show();
/*
    QFrame frame;
    frame.show();

    MyCanvas SFMLView(&frame, QPoint(0, 0), QSize(100, 100));
    SFMLView.show();
*/
    return a.exec();
}
