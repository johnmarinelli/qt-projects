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
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, mWindowWidth, mWindowHeight);
    setGUI();
    mSFMLFrame = ui->SFMLFrame;

    mTilesheet.loadFromFile("tiles.png");
    QPixmap tileSheet(":/tiles/assets/tiles.png");

    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(),mSFMLFrame->geometry().height()),
                             mTilesheet);

    mSignalMapper = new QSignalMapper(this);

    //int radioButtonX = mSFMLFrame->geometry().left() + mSFMLFrame->geometry().width() + 10;
    //int radioButtonY = 75;

    /*
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            int xOffset = (j*mTileWidth)+j;
            int yOffset = (i*mTileHeight)+i;

            QPixmap tile = tileSheet.copy(xOffset, yOffset, mTileWidth, mTileHeight);

            JRadioButton* jrb = new JRadioButton("", mTilesheet, this);

            jrb->setIcon(QIcon(tile));
            jrb->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);

            int radioButtonWidth = tile.rect().width()*2;
            int radioButtonHeight = jrb->geometry().height();

            jrb->setGeometry(radioButtonX, radioButtonY, radioButtonWidth, radioButtonHeight);

            connect(jrb, SIGNAL(clicked()), mSignalMapper, SLOT(map()));

            sf::Rect<int> subRect = jrb->getClipBounds();
            QObject* a = new QObject();
            QRect rect;
            rect.setTop(subRect.top);
            rect.setLeft(subRect.left);
            rect.setWidth(subRect.width);
            rect.setHeight(subRect.height);

            mObjects.push_back(a);

            a->setProperty("bounds", QVariant(rect));

            mSignalMapper->setMapping(jrb, mObjects.back());

            mRadioButtons.push_back(jrb);

            if(radioButtonY + radioButtonHeight >= this->geometry().height() - (radioButtonHeight*2) ) {
                radioButtonY = 75;
                radioButtonX += 75;
            }
            else {
                radioButtonY += radioButtonHeight;
            }
        }
    }*/

    //connect(mSignalMapper, SIGNAL(mapped(QObject*)), mSFMLView, SLOT(setCurrentTileBounds(QObject*)));
}

void MainWindow::setGUI()
{
    /* left to right */
    setTileSelectLayout();
    resizeSFMLFrame();
}

void MainWindow::setTileSelectLayout()
{
    ui->scrollArea->setGeometry(0, 0, mWindowWidth / 3, mWindowHeight);
    QPixmap tileSheet(":/tiles/assets/tiles.png");
    int tileSheetCols = std::floor(tileSheet.width() / mTileWidth);
    int tileSheetRows = std::floor(tileSheet.height() / mTileHeight);

    /* layout for scrollarea */
    QGridLayout* layout = new QGridLayout(ui->scrollArea);
    ui->scrollAreaWidgetContents->setLayout(layout);

    int gridCols = std::floor(ui->scrollArea->geometry().width() / mTileWidth);
    int gridRows = std::floor(ui->scrollArea->geometry().height() / mTileHeight);

    for(int i = 0; i < tileSheetRows; ++i) {
        for(int j = 0; j < tileSheetCols; ++j) {
            int xOffset = (j*mTileWidth)+j;
            int yOffset = (i*mTileHeight)+i;

            /* clip tilesheet to x, y, tilewidth, tileheight */
            QPixmap tile = tileSheet.copy(xOffset, yOffset, mTileWidth, mTileHeight);

            /* create new push button */
            QPushButton* button = new QPushButton(this);

            /* set button's icon */
            button->setIcon(QIcon(tile));
            button->setMaximumSize(mTileWidth, mTileHeight);

            int col = i%gridRows;
            int row = j%gridCols;
            layout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }
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
