#include "mycanvas.h"
#include "utility.h"
#include <iostream>
#include <sstream>

MyCanvas::MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, sf::Texture& tilesheet) :
    QSFMLCanvas(parent, position, size),
    mTilesheet(tilesheet),
    mSize(size)
{
}

void MyCanvas::onInit()
{
}

void MyCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color(255, 255, 255));
    for(auto sprite : mSprites) {
        draw(sprite);
    }
}

void MyCanvas::setCurrentTileName(QString name)
{
    mCurrentTileName = name.toUtf8().constData();
}

void MyCanvas::setCurrentTileBounds(QObject* bounds)
{
    QRect r = bounds->property("bounds").toRect();

    qDebug(std::to_string(r.left()).c_str());

    mCurrentTileBounds.left = r.left();
    mCurrentTileBounds.top = r.top();
    mCurrentTileBounds.width = r.width();
    mCurrentTileBounds.height = r.height();
}

void MyCanvas::mousePressEvent(QMouseEvent* event)
{
    if(event->button() & Qt::LeftButton) {
        int x = event->pos().x();
        int y = event->pos().y();

        std::stringstream sX;
        sX << x;
        std::stringstream sY;
        sY << y;

        std::string s = "x: " + sX.str() + " y: " + sY.str();

        sf::Sprite sprite;

        sprite.setTexture(mTilesheet);
        sprite.setTextureRect(mCurrentTileBounds);

        x = getNearestMultiple(x, TILE_WIDTH);
        y = getNearestMultiple(y, TILE_HEIGHT);

        sprite.setPosition(x, y);

        mSprites.push_back(sprite);
    }
}
