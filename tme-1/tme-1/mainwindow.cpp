#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jradiobutton.h"
#include "qsfmlrect.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDir>
#include <QString>

#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, mWindowWidth, mWindowHeight);
    //setGUI();
    resizeTileSelect();
    resizeSFMLFrame();

    mTilesheet.loadFromFile("tiles.png");

    mSFMLFrame = ui->SFMLFrame;
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(), mSFMLFrame->geometry().height()),
                             mTilesheet);
    setTileSelectLayout();
}

void MainWindow::setGUI()
{
    /* left to right */
    resizeTileSelect();
    setTileSelectLayout();
    resizeSFMLFrame();
}

void MainWindow::resizeTileSelect()
{
    ui->scrollArea->setGeometry(0, 0, mWindowWidth / 3, mWindowHeight);
}

void MainWindow::setTileSelectLayout()
{
    QPixmap tileSheet(":/tiles/assets/tiles.png");
    int tileSheetCols = std::floor(tileSheet.width() / mTileWidth);
    int tileSheetRows = std::floor(tileSheet.height() / mTileHeight);

    /* layout for scrollarea */
    QGridLayout* layout = new QGridLayout(ui->scrollArea);
    ui->scrollAreaWidgetContents->setLayout(layout);

    int gridCols = std::floor(ui->scrollArea->geometry().width() / mTileWidth);
    int gridRows = std::floor(ui->scrollArea->geometry().height() / mTileHeight);

    mSignalMapper = new QSignalMapper(this);

    for(int i = 0; i < tileSheetRows; ++i) {
        for(int j = 0; j < tileSheetCols; ++j) {
            int xOffset = (j*mTileWidth)+j;
            int yOffset = (i*mTileHeight)+i;

            /* clip tilesheet to x, y, tilewidth, tileheight */
            QPixmap tile = tileSheet.copy(xOffset, yOffset, mTileWidth, mTileHeight);

            /* create new push button */
            JPushButton* button = new JPushButton(this);

            button->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);
            connect(button, SIGNAL(clicked()), mSignalMapper, SLOT(map()));

            sf::Rect<int> subRect = button->getClipBounds();
            QObject* package = new QObject();
            QRect rect;
            rect.setTop(subRect.top);
            rect.setLeft(subRect.left);
            rect.setWidth(subRect.width);
            rect.setHeight(subRect.height);
            package->setProperty("bounds", QVariant(rect));

            mObjects.push_back(package);
            mSignalMapper->setMapping(button, mObjects.back());

            /* set button's icon */
            button->setIcon(QIcon(tile));
            button->setMaximumSize(mTileWidth, mTileHeight);

            int col = i%gridRows;
            int row = j%gridCols;
            layout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }

    connect(mSignalMapper, SIGNAL(mapped(QObject*)), mSFMLView, SLOT(setCurrentTileBounds(QObject*)));
}

void MainWindow::resizeSFMLFrame()
{
    QRect scrollAreaRect = ui->scrollArea->geometry();
    int x = scrollAreaRect.x() + scrollAreaRect.width();
    int width = mWindowWidth - scrollAreaRect.width();

    ui->SFMLFrame->setGeometry(x, 0,
                            width, mWindowHeight);
}

MainWindow::~MainWindow()
{
    delete ui;
}
