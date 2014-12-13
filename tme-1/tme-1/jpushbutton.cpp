#include "jpushbutton.h"

JPushButton::JPushButton(QWidget *parent) :
    QPushButton(parent),
    mClipBounds(0, 0, 0, 0)
{
}

void JPushButton::setClipBounds(int top, int left, int width, int height)
{
    mClipBounds.top = top;
    mClipBounds.left = left;
    mClipBounds.width = width;
    mClipBounds.height = height;
}

sf::Rect<int> JPushButton::getClipBounds()
{
    return mClipBounds;
}
