#include "jradiobutton.h"

JRadioButton::JRadioButton(const QString& text, QWidget *parent) :
    QRadioButton(text, parent)
{
}

void JRadioButton::setIconPath(const QString path)
{
    this->mIconPath = path;
    qDebug(mIconPath.toUtf8().constData());
}

