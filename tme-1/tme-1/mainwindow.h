#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include "jpushbutton.h"
#include "tilesheethandler.h"
#include "tile.h"

#include <QMainWindow>
#include <QRadioButton>
#include <QFrame>
#include <QSignalMapper>
#include <QScrollArea>

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void setTileSelectLayout(QScrollArea* scrollArea, QWidget* scrollAreaContents, const TileSheet& tileSheet);
    void setCurrentTileFrameLayout();
    void resizeCurrentTileFrame();
    void resizeTileSelect();
    void resizeSFMLFrame();

    ~MainWindow();

private slots:
    void sendTileInformation(const Tile& tile);
    void sendTraversableInformation(const QString& str);

private:
    Ui::MainWindow *ui;

    QSignalMapper* mSignalMapper;

    QFrame* mInputFrame;
    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;

    TileSheet mTileSheet;
    TileSheetHandler mTileSheets;

    std::vector<QObject*> mObjects;

    std::vector<JPushButton*> mPushButtons;

    const int mTileWidth = 32;
    const int mTileHeight = 32;

    int mWindowWidth;
    int mWindowHeight;
};

#endif // MAINWINDOW_H
