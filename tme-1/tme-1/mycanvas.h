#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "qsfmlrect.h"
#include <QMouseEvent>

/*
 * TODO:
 * use a std::map for tiles
 * std::map<Vector2d, sf::Sprite, comparatorFn> mSprites
 * where Vector2d is the x, y coords
 * and comparatorFn is a functor:
 * struct comparatorFn{
 *   bool operator()(const Vector2d& a, const Vector2d& b) {
 *     return a.x == b.x && a.y == b.y;
 *   }
 * };
 */

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

    sf::Sprite findTile(int x, int y);

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
