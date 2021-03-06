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
    void resizeSFMLFrame(QFrame* frame);
    void setCanvasScrollAreaLayout(QScrollArea* scrollArea, QWidget* scrollAreaWidgetContents);
    void resizeCanvasScrollArea(QFrame* frame, QScrollArea* scrollArea, QWidget* scrollAreaWidget);

    ~MainWindow();

private slots:
    void sendTileInformation(const Tile& tile);
    void sendTraversableInformation(const QString& str);
    void setCurrentTileSheetIndex(int index);
    void showNewMapDialog();
    void makeNewMap(std::tuple<int, int, int, int> params);
    void saveMap();

private:

    void setTileSelectButtons();
    void createNewCanvasArea(int width=0, int height=0, int tileWidth=0, int tileHeight=0);

    Ui::MainWindow *ui;

    QFrame* mInputFrame;
    MyCanvas* mSFMLView;

    TileSheetHandler mTileSheetHandler;
    unsigned short mTileSheetIndex;

    int mTileWidth;
    int mTileHeight;

    int mWindowWidth;
    int mWindowHeight;
};

#endif // MAINWINDOW_H
