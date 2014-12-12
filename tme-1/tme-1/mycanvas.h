#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "qsfmlrect.h"
#include <QMouseEvent>

class MyCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();

    sf::Texture mTexture;
    sf::Texture mTilesheet;
    std::vector<sf::Sprite> mSprites;
    sf::Sprite mSprite;

    std::string mCurrentTileName;

    sf::Rect<int> mCurrentTileBounds;

    QSize mSize;

public:
    MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, sf::Texture& tilesheet);

signals:

public slots:
    void setCurrentTileName(QString name);
    void setCurrentTileBounds(QObject* bounds);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
