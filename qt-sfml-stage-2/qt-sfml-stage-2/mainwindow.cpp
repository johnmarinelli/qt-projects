#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jradiobutton.h"

#include <QMessageBox>
#include <QDir>
#include <QString>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSFMLFrame = this->findChild<QFrame*>("SFMLFrame");
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(),mSFMLFrame->geometry().height()));

    mSignalMapper = new QSignalMapper(this);

    /*
     * for each tile in tiles, create a radio button
     */
    int radioButtonX = mSFMLFrame->geometry().left() + mSFMLFrame->geometry().width() + 10;
    int radioButtonY = 75;
    int radioButtonYIncrement = 100;

    foreach(const QString& imgPath, QDir(":/tiles/assets").entryList()) {
        JRadioButton* jrb = new JRadioButton("", this);

        QString path = ":/tiles/assets/" + imgPath;
        QPixmap iconPic(path);

        jrb->setIcon(QIcon(iconPic));
        jrb->setIconPath(imgPath);

        int radioButtonWidth = iconPic.rect().width() + jrb->geometry().width();
        int radioButtonHeight = iconPic.rect().height() + jrb->geometry().height();

        jrb->setGeometry(radioButtonX, radioButtonY, radioButtonWidth, radioButtonHeight);

        connect(jrb, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
        mSignalMapper->setMapping(jrb, imgPath);

        mRadioButtons.push_back(jrb);
        radioButtonY += radioButtonYIncrement;
    }

    connect(mSignalMapper, SIGNAL(mapped(QString)), mSFMLView, SLOT(setCurrentTileName(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
