#include "mycanvas.h"
#include <iostream>
#include <sstream>

MyCanvas::MyCanvas(QWidget *parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size)
{
}

void MyCanvas::onInit()
{
   mTexture.loadFromFile("../qt-sfml-stage-2/assets/chest.png");
   mSprite.setTexture(mTexture);
}

void MyCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color(255, 255, 255));
    draw(mSprite);
}

void MyCanvas::setCurrentTileName(QString name)
{
    mCurrentTileName = name.toUtf8().constData();
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

        /*
         * load corresponding image into mSprite
         */
        std::string imgPath = "../qt-sfml-stage-2/assets/" + mCurrentTileName;

        mTexture.loadFromFile(imgPath);
        mSprite.setTexture(mTexture);

        qDebug(s.c_str());

        mSprite.setPosition(x, y);
    }
}
