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

    void setTileSelectLayout(QScrollArea* scrollArea, QWidget* scrollAreaContents, const std::shared_ptr<const TileSheet>& tileSheet);
    void setCurrentTileFrameLayout();
    void resizeCurrentTileFrame();
    void resizeTileSelect();
    void resizeSFMLFrame();

    ~MainWindow();

private slots:
    void sendTileInformation(const Tile& tile);
    void sendTraversableInformation(const QString& str);
    void setCurrentTileSheetIndex(int index);

private:
    Ui::MainWindow *ui;

    QFrame* mInputFrame;
    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;

    TileSheetHandler mTileSheetHandler;
    unsigned short mTileSheetIndex;

    const int mTileWidth = 32;
    const int mTileHeight = 32;

    int mWindowWidth;
    int mWindowHeight;
};

#endif // MAINWINDOW_H
