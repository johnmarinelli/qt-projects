#include "newmapdialog.h"
#include <QLabel>
#include <QIntValidator>
#include <tuple>
#include <iostream>

NewMapDialog::NewMapDialog(QWidget *parent) :
    QDialog(parent),
    mWidthInput(new QLineEdit(this)),
    mHeightInput(new QLineEdit(this)),
    mConfirm(new QPushButton("Create", this)),
    mLayout(new QVBoxLayout(this))
{
    QIntValidator qiv(0, std::numeric_limits<int>::max());

    mWidthInput->setValidator(&qiv);
    mHeightInput->setValidator(&qiv);

    QLabel* widthLabel = new QLabel("Width: ", this);
    QLabel* heightLabel = new QLabel("Height: ", this);

    mLayout->addWidget(widthLabel, 0, Qt::AlignLeft);
    mLayout->addWidget(mWidthInput, 1, Qt::AlignRight);
    mLayout->addWidget(heightLabel, 0, Qt::AlignLeft);
    mLayout->addWidget(mHeightInput, 1, Qt::AlignRight);

    mLayout->addWidget(mConfirm, 1, Qt::AlignCenter);

    /* remap the clicked() to a custom slot */
    connect(mConfirm, SIGNAL(clicked()), this, SLOT(sendNewMapInfo()));
}
void NewMapDialog::sendNewMapInfo()
{
    try{
        mWidth = std::stoi(mWidthInput->text().toStdString());
        mHeight = std::stoi(mHeightInput->text().toStdString());

        auto package = std::make_tuple(mWidth, mHeight);
        emit makeNew(package);
    }
    catch(const std::invalid_argument& e) {
        /* if stoi is "" */
        std::cout << e.what() << std::endl;
    }
}
