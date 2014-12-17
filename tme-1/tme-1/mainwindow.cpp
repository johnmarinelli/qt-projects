#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    mQTTileSheet(":/tiles/assets/tiles.png"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, mWindowWidth, mWindowHeight);
    resizeCurrentTileFrame();
    resizeTileSelect();
    resizeSFMLFrame();

    mTilesheet.loadFromFile("tiles.png");

    mSFMLFrame = ui->SFMLFrame;
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(), mSFMLFrame->geometry().height()),
                             mTilesheet);
    setCurrentTileFrameLayout();
    setTileSelectLayout();

    connect(mSFMLView, SIGNAL(clicked(const Tile&)), this, SLOT(sendTileInformation(const Tile&)));
}

void MainWindow::sendTileInformation(const Tile& tile)
{
    int xOffset = tile.getTileSheetCoords().x;
    int yOffset = tile.getTileSheetCoords().y;
    int tileWidth = tile.getDimensions().x;
    int tileHeight = tile.getDimensions().y;

    int destWidth = ui->currentTileGraphic->geometry().width();
    int destHeight = ui->currentTileGraphic->geometry().height();

    /* clip tilesheet to x, y, tilewidth, tileheight */
    QPixmap gfx = mQTTileSheet.copy(xOffset, yOffset, tileWidth, tileHeight)
                              .scaled(QSize(destWidth, destHeight), Qt::IgnoreAspectRatio);

    ui->currentTileGraphic->setPixmap(gfx);

    /* set coordinate texts */
    std::string worldCoordText = "World Position ";
    worldCoordText.append(std::to_string(tile.getCoords().x));
    worldCoordText.append(", ");
    worldCoordText.append(std::to_string(tile.getCoords().y));
    ui->currentTileWorldCoords->setText(QString(worldCoordText.c_str()));


    std::string tileSheetCoordText = "Tilesheet Position ";
    tileSheetCoordText.append(std::to_string(xOffset));
    tileSheetCoordText.append(", ");
    tileSheetCoordText.append(std::to_string(yOffset));
    ui->currentTileTileSheetCoords->setText(QString(tileSheetCoordText.c_str()));
}

void MainWindow::setTileSelectLayout()
{

    int tileSheetCols = std::floor(mQTTileSheet.width() / mTileWidth);
    int tileSheetRows = std::floor(mQTTileSheet.height() / mTileHeight);

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
            QPixmap tile = mQTTileSheet.copy(xOffset, yOffset, mTileWidth, mTileHeight);

            /* create new push button */
            JPushButton* button = new JPushButton(this);

            button->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);

            /* when button is clicked, mSignalMapper->map() is called */
            connect(button, SIGNAL(clicked()), mSignalMapper, SLOT(map()));

            /* send package to canvas */
            sf::Rect<int> subRect = button->getClipBounds();
            QObject* package = new QObject();
            QRect rect;
            rect.setTop(subRect.top);
            rect.setLeft(subRect.left);
            rect.setWidth(subRect.width);
            rect.setHeight(subRect.height);
            package->setProperty("bounds", QVariant(rect));

            mObjects.push_back(package);

            /* let mSignalMapper know which action should pass which argument */
            mSignalMapper->setMapping(button, mObjects.back());

            /* set button's icon */
            button->setIcon(QIcon(tile));
            button->setMaximumSize(mTileWidth, mTileHeight);

            int col = i%gridRows;
            int row = j%gridCols;
            layout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }

    /*
     * when mSignalMapper emits a SIGNAL(mapped(QObject*)),
     * mSFMLView->setCurrentTileBounds(QObject*) gets called
    */
    connect(mSignalMapper, SIGNAL(mapped(QObject*)), mSFMLView, SLOT(setCurrentTileBounds(QObject*)));
}

void MainWindow::setCurrentTileFrameLayout()
{
    /* layout for current tile frame */
    QGridLayout* layout = new QGridLayout(ui->currentTileFrame);
    ui->currentTileFrame->setLayout(layout);
    ui->currentTileGraphic->setFixedSize(128, 128);
    layout->addWidget(ui->currentTileGraphic, 0, 0, 5, 5, Qt::AlignTop);

    /* set coordinate texts & traversable combo box */
    layout->addWidget(ui->currentTileWorldCoords, 2, 0, 5, 5, Qt::AlignLeft);
    layout->addWidget(ui->currentTileTileSheetCoords, 3, 0, 5, 5, Qt::AlignLeft);
    layout->addWidget(ui->traversableLabel, 4, 0, 5, 5, Qt::AlignLeft);
    layout->addWidget(ui->currentTileTraversable, 4, 1, 5, 5, Qt::AlignRight);
}

void MainWindow::resizeCurrentTileFrame()
{
    ui->currentTileFrame->setGeometry(0, 0, mWindowWidth / 3, mWindowHeight / 2);
}

void MainWindow::resizeTileSelect()
{
    ui->scrollArea->setGeometry(0, mWindowHeight / 2, mWindowWidth / 3, mWindowHeight / 2);
}

void MainWindow::resizeSFMLFrame()
{
    QRect scrollAreaRect = ui->scrollArea->geometry();
    int x = scrollAreaRect.x() + scrollAreaRect.width();
    int width = mWindowWidth - scrollAreaRect.width();

    ui->SFMLFrame->setGeometry(x, 0, width, mWindowHeight);
}

MainWindow::~MainWindow()
{
    delete ui;
}
