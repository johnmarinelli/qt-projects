#include "mainwindow.h"
#include "mycanvas.h"
#include <QApplication>
#include <QFrame>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFrame frame;
    frame.show();

    MyCanvas SFMLView(&frame, QPoint(0, 0), QSize(100, 100));
    SFMLView.show();

    int ret = a.exec();

    return ret;
}
