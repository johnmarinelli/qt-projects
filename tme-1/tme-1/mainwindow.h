#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include "jradiobutton.h"
#include "jpushbutton.h"

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

    void setGUI();
    void setTileSelectLayout();
    void resizeTileSelect();
    void resizeSFMLFrame();

    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    QSignalMapper* mSignalMapper;

    QFrame* mInputFrame;
    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;
    sf::Texture mTilesheet;

    std::vector<JRadioButton*> mRadioButtons;
    std::vector<QObject*> mObjects;

    std::vector<JPushButton*> mPushButtons;

    const int mTileWidth = 32;
    const int mTileHeight = 32;

    const int mWindowWidth = 700;
    const int mWindowHeight = 700;
};

#endif // MAINWINDOW_H
