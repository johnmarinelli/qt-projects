#include "mycanvas.h"

MyCanvas::MyCanvas(QWidget *parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size)
{
}

void MyCanvas::onInit()
{
    mTexture.loadFromFile("pic.png");
    mSprite.setTexture(mTexture);
}

void MyCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color(0, 0, 0));
    draw(mSprite);
}
