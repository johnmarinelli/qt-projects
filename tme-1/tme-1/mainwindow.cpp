#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsfmlrect.h"
#include "utility.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDesktopWidget>
#include <QDir>
#include <QString>
#include <QDirIterator>

#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mWindowWidth(0),
    mWindowHeight(0),
    mTileSheetIndex(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    mWindowWidth = QApplication::desktop()->availableGeometry().width();
    mWindowHeight = QApplication::desktop()->availableGeometry().height();
    this->setGeometry(0, 0, mWindowWidth, mWindowHeight);

    resizeCurrentTileFrame();
    resizeTileSelect();
    resizeSFMLFrame();

    mSFMLFrame = ui->SFMLFrame;
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(), mSFMLFrame->geometry().height()),
                             mTileSheetHandler);

    /* add all tilesheets to mTileSheetHandler */
    QDir assetsDir("../tme-1/assets");
    QFileInfoList fileInfoList = assetsDir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries);

    std::for_each(fileInfoList.begin(), fileInfoList.end(), [this](const QFileInfo& fileInfo) {
        /* add tilesheet to our vector */
        int index = mTileSheetHandler.add(fileInfo.absoluteFilePath().toStdString(), QSize(32, 32));

        /* add a new tab with scroll area */
        QWidget* tab = new QWidget(ui->tileSheetTabs);
        QRect tabViewRect = ui->tileSheetTabs->geometry();

        /* add tab's layout */
        QGridLayout* tabGridLayout = new QGridLayout(tab);
        tab->setLayout(tabGridLayout);
        tab->setGeometry(tabViewRect);

        /* create a scroll area for this tilesheet */
        QScrollArea* scrollArea = new QScrollArea(tab);
        QWidget* scrollAreaContents = new QWidget(scrollArea);
        scrollArea->setWidget(scrollAreaContents);

        /* add scroll area to tab's layout */
        tabGridLayout->addWidget(scrollArea);

        QRect tabRect = tab->geometry();
        scrollArea->setGeometry(tabRect);
        scrollAreaContents->setGeometry(tabRect);

        /* set scroll area's layout */
        this->setTileSelectLayout(scrollArea, scrollAreaContents, *(mTileSheetHandler.get(index).get()));
        ui->tileSheetTabs->addTab(tab, QString(std::to_string(index).c_str()));
    });

//    mTileSheet = *(mTileSheetHandler.get(mTileSheetTabIndex));

    setCurrentTileFrameLayout();

    /* connect canvas to tile information frame */
    connect(mSFMLView, SIGNAL(clicked(const Tile&)), this, SLOT(sendTileInformation(const Tile&)));

    /* connect tile information frame to current tile selected */
    connect(ui->currentTileTraversable, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(sendTraversableInformation(const QString&)));

    /* connect tab switching to change mTileSheet */
    connect(ui->tileSheetTabs, SIGNAL(currentChanged(int)), mSFMLView, SLOT(setCurrentTileSheetIndex(int)));
    connect(ui->tileSheetTabs, SIGNAL(currentChanged(int)), this, SLOT(setCurrentTileSheetIndex(int)));
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
    QPixmap gfx = mTileSheetHandler.get(mTileSheetIndex)->getQtTileSheet().copy(xOffset, yOffset, tileWidth, tileHeight)
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

    /* set if tile is traversable or not */
    int index = ui->currentTileTraversable->findText(boolToString(tile.getTraversable()));
    if(-1 != index) {
        ui->currentTileTraversable->setCurrentIndex(index);
    }
}

void MainWindow::sendTraversableInformation(const QString& str)
{
    bool isTraversable = false;

    if(!str.compare(QString("True"), Qt::CaseInsensitive)) {
        isTraversable = true;
    }

    mSFMLView->setCurrentTileTraversable(isTraversable);
}

void MainWindow::setTileSelectLayout(QScrollArea* scrollArea, QWidget* scrollAreaContents, const TileSheet& tileSheet)
{
    int tileSheetCols = tileSheet.getColumns();
    int tileSheetRows = tileSheet.getRows();

    /* layout for scrollarea */
    QGridLayout* layout = new QGridLayout(scrollAreaContents);

    scrollAreaContents->setLayout(layout);

    int gridCols = std::floor(scrollArea->geometry().width() / mTileWidth);
    int gridRows = std::floor(scrollArea->geometry().height() / mTileHeight);

    for(int i = 0; i < tileSheetRows; ++i) {
        for(int j = 0; j < tileSheetCols; ++j) {
            int xOffset = (j*mTileWidth)+j;
            int yOffset = (i*mTileHeight)+i;

            /* clip tilesheet to x, y, tilewidth, tileheight for tile icon*/
            QPixmap tile = tileSheet.getQtTileSheet().copy(xOffset, yOffset, mTileWidth, mTileHeight);

            /* create new push button */
            JPushButton* button = new JPushButton(this, &tileSheet);

            button->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);

            /* connect tile selector to canvas */
            connect(button, SIGNAL(clicked(const sf::Rect<int>&, std::shared_ptr<const TileSheet>)),
                mSFMLView, SLOT(setCurrentTile(const sf::Rect<int>&, std::shared_ptr<const TileSheet>)));

            /* set button's icon */
            button->setIcon(QIcon(tile));
            button->setMaximumSize(mTileWidth, mTileHeight);

            int col = i%gridRows;
            int row = j%gridCols;
            layout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }
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

void MainWindow::setCurrentTileSheetIndex(int index)
{
    mTileSheetIndex = index;
}

void MainWindow::resizeCurrentTileFrame()
{
    ui->currentTileFrame->setGeometry(0, 0, mWindowWidth / 3, mWindowHeight / 2);
}

void MainWindow::resizeTileSelect()
{
    ui->tileSheetTabs->setGeometry(0, mWindowHeight / 2, mWindowWidth / 3, mWindowHeight / 2);
}

void MainWindow::resizeSFMLFrame()
{
    QRect tabViewRect = ui->tileSheetTabs->geometry();
    int x = tabViewRect.x() + tabViewRect.width();
    int width = mWindowWidth - tabViewRect.width();

    ui->SFMLFrame->setGeometry(x, 0, width, mWindowHeight);
}

MainWindow::~MainWindow()
{
    delete ui;
}
