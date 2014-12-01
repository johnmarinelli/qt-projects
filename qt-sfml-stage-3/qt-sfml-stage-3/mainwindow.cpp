#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jradiobutton.h"
#include "qsfmlrect.h"

#include <QMessageBox>
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
    mTilesheet.loadFromFile("tiles.png");

    mSFMLFrame = this->findChild<QFrame*>("SFMLFrame");
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(),mSFMLFrame->geometry().height()),
                             mTilesheet);

    QPixmap tileSheet(":/tiles/assets/tiles.png");

    int cols = std::floor(tileSheet.width() / mTileWidth);
    int rows = std::floor(tileSheet.height() / mTileHeight);

    mSignalMapper = new QSignalMapper(this);

    int radioButtonX = mSFMLFrame->geometry().left() + mSFMLFrame->geometry().width() + 10;
    int radioButtonY = 75;
    int radioButtonYIncrement = 25;

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            int xOffset = (j*mTileWidth)+j;
            int yOffset = (i*mTileHeight)+i;

            QPixmap tile = tileSheet.copy(xOffset, yOffset, mTileWidth, mTileHeight);

            JRadioButton* jrb = new JRadioButton("", mTilesheet, this);

            jrb->setIcon(QIcon(tile));
            jrb->setClipBounds(yOffset, xOffset, mTileWidth, mTileHeight);

            int radioButtonWidth = tile.rect().width()*2;// + jrb->geometry().width();
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
    }

    connect(mSignalMapper, SIGNAL(mapped(QObject*)), mSFMLView, SLOT(setCurrentTileBounds(QObject*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
