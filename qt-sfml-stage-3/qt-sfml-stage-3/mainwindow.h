#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include "jradiobutton.h"

#include <QMainWindow>
#include <QRadioButton>
#include <QFrame>
#include <QSignalMapper>

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    QSignalMapper* mSignalMapper;

    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;
    sf::Texture mTilesheet;

    std::vector<JRadioButton*> mRadioButtons;
    std::vector<QObject*> mObjects;

    const int mTileWidth = 32;
    const int mTileHeight = 32;

    const int mWindowWidth = 1000;
    const int mWindowHeight = 1000;
};

#endif // MAINWINDOW_H
