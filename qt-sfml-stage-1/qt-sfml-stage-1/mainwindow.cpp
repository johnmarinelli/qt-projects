#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSFMLFrame = this->findChild<QFrame*>("frame");
    mSFMLView = new MyCanvas(mSFMLFrame, QPoint(0,0),
                             QSize(mSFMLFrame->geometry().width(),mSFMLFrame->geometry().height()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_released()
{
    QMessageBox alert;
    alert.setText("YOU PRESSED THE FIRST RADIO BUTTON");
    alert.exec();

    QAbstractButton* w = (QAbstractButton*)this->sender();
    std::string name = w->objectName().toUtf8().constData();

    mSFMLView->setCurrentTileName(name);
    qDebug(name.c_str());
}

void MainWindow::on_radioButton_2_released()
{
    QMessageBox alert;
    alert.setText("YOU PRESSED THE SECOND RADIO BUTTON");
    alert.exec();

    QAbstractButton* w = (QAbstractButton*)this->sender();
    std::string name = w->objectName().toUtf8().constData();

    mSFMLView->setCurrentTileName(name);
    qDebug(name.c_str());
}

void MainWindow::on_radioButton_3_released()
{
    QMessageBox alert;
    alert.setText("YOU PRESSED THE THIRD RADIO BUTTON");
    alert.exec();
}

void MainWindow::on_radioButton_4_released()
{
    QMessageBox alert;
    alert.setText("YOU PRESSED THE FOURTH RADIO BUTTON");
    alert.exec();
}
