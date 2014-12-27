#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newmapdialog.h"
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
    ui(new Ui::MainWindow),
    mTileSheetIndex(0),
    mTileWidth(DEFAULT_TILE_WIDTH),
    mTileHeight(DEFAULT_TILE_HEIGHT),
    mWindowWidth(0),
    mWindowHeight(0)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    mWindowWidth = QApplication::desktop()->availableGeometry().width();
    mWindowHeight = QApplication::desktop()->availableGeometry().height();
    this->setGeometry(0, 0, mWindowWidth, mWindowHeight);

    resizeCurrentTileFrame();
    resizeTileSelect();
    resizeSFMLFrame();

    mSFMLView = new MyCanvas(ui->canvasScrollAreaWidgetContents, QPoint(0,0),
                             QSize(ui->SFMLFrame->geometry().width(), ui->SFMLFrame->geometry().height()),
                             mTileSheetHandler,
                             mTileWidth, mTileHeight);

    setCanvasScrollAreaLayout();
    resizeCanvasScrollArea();

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
        this->setTileSelectLayout(scrollArea, scrollAreaContents, mTileSheetHandler.get(index));
        ui->tileSheetTabs->addTab(tab, QString(std::to_string(index).c_str()));
    });

    setCurrentTileFrameLayout();

    /* connect canvas to tile information frame */
    connect(mSFMLView, SIGNAL(clicked(const Tile&)), this, SLOT(sendTileInformation(const Tile&)));

    /* connect tile information frame to current tile selected */
    connect(ui->currentTileTraversable, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(sendTraversableInformation(const QString&)));

    /* connect tab switching to change mTileSheet */
    connect(ui->tileSheetTabs, SIGNAL(currentChanged(int)), mSFMLView, SLOT(setCurrentTileSheetIndex(int)));
    connect(ui->tileSheetTabs, SIGNAL(currentChanged(int)), this, SLOT(setCurrentTileSheetIndex(int)));

    /* connect new file option to new map dialog */
    connect(ui->newMapAction, SIGNAL(triggered()), this, SLOT(showNewMapDialog()));
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
    QPixmap gfx = mTileSheetHandler.get(tile.getTileSheetIndex())->getQtTileSheet().copy(xOffset, yOffset, tileWidth, tileHeight)
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

void MainWindow::setTileSelectLayout(QScrollArea* scrollArea, QWidget* scrollAreaContents, const std::shared_ptr<const TileSheet>& tileSheet)
{
    int tileSheetCols = tileSheet->getColumns();
    int tileSheetRows = tileSheet->getRows();

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
            QPixmap tile = tileSheet->getQtTileSheet().copy(xOffset, yOffset, mTileWidth, mTileHeight);

            /* create new push button */
            JPushButton* button = new JPushButton(this, tileSheet);

            button->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);

            /* connect tile selector to canvas */
            connect(button, SIGNAL(clicked(const sf::Rect<int>&, const std::shared_ptr<const TileSheet>)),
                mSFMLView, SLOT(setCurrentTile(const sf::Rect<int>&, const std::shared_ptr<const TileSheet>)));

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

void MainWindow::showNewMapDialog()
{
    /* start new map dialog */
    NewMapDialog* nmd = new NewMapDialog(this);
    nmd->show();

    connect(nmd, SIGNAL(makeNew(std::tuple<int,int>)), this, SLOT(makeNewMap(std::tuple<int, int>)));
}

void MainWindow::makeNewMap(std::tuple<int, int> params)
{
    /*
     * width, height: ints
     */
    auto width = std::get<0>(params);
    auto height = std::get<1>(params);

    auto rect = ui->SFMLFrame->geometry();

    /*
     * todo: create a new map & connect it appropriately
     */
    mSFMLView->reset();

    mSFMLView->setTileDimensions(DEFAULT_TILE_WIDTH, DEFAULT_TILE_HEIGHT);
    mSFMLView->resize(width, height);
    mSFMLView->setLines();

    setCanvasScrollAreaLayout();
    //resizeCanvasScrollArea();

    std::cout << mSFMLView->size().width() << std::endl;
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

/*
 * canvas scroll area design depends on mSFMLView
 */
void MainWindow::setCanvasScrollAreaLayout()
{
    ui->canvasScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->canvasScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    removeLayout(ui->canvasScrollAreaWidgetContents->layout());

    QGridLayout* layout = new QGridLayout(ui->canvasScrollAreaWidgetContents);
    ui->canvasScrollAreaWidgetContents->setLayout(layout);
    ui->canvasScrollArea->setWidgetResizable(false);
    layout->addWidget(mSFMLView, 0, 0);
}

void MainWindow::resizeCanvasScrollArea()
{
    QRect SFMLFrameRect = ui->SFMLFrame->geometry();

    /* size of actual scroll area */
    ui->canvasScrollArea->setGeometry(0, 0, SFMLFrameRect.width(), SFMLFrameRect.height() - 50);

    /* size of scroll area contents; determines scroll bars */
     ui->canvasScrollAreaWidgetContents->resize(mSFMLView->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}
