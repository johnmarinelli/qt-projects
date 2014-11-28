#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mThirdTile = new QRadioButton("", this);
    connect(mThirdTile, SIGNAL(clicked()), this, SLOT(on_radioButton_3_released()));
    mThirdTile->setAutoExclusive(false);
    mThirdTile->setObjectName("radiobutton_3");
    mThirdTile->setGeometry(0, 100, 61, 41);
    mThirdTile->setIcon(QIcon(":/assets/grass.png"));

    mFourthTile = new QRadioButton("", this);
    connect(mFourthTile, SIGNAL(clicked()), this, SLOT(on_radioButton_4_released()));
    mFourthTile->setAutoExclusive(false);
    mFourthTile->setObjectName("radiobutton_4");
    mFourthTile->setGeometry(0, 150, 61, 41);
    //mFourthTile->setIcon(QIcon(":/assets/grass.png"));
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
}

void MainWindow::on_radioButton_2_released()
{
    QMessageBox alert;
    alert.setText("YOU PRESSED THE SECOND RADIO BUTTON");
    alert.exec();
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
