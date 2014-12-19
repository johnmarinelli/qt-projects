#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "qsfmlrect.h"
#include "line.h"
#include "tile.h"

#include <iostream>
#include <unordered_map>
#include <QMouseEvent>

/*
 * functor to hash keys.
 * XOR the key.x with (key.y << 1) and bitshift >> 1
 */
struct Vector2iHash {
    std::size_t operator()(const sf::Vector2i& key) const {
        return std::hash<int>()(key.x ^
                    (std::hash<int>()(key.y)
                    << 1)
                 >> 1);
    }
};

class MyCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();

    sf::Texture mTilesheet;
    std::unordered_map<sf::Vector2i, Tile, Vector2iHash> mTiles;
    Tile* mSelectedTile;

    sf::Rect<int> mCurrentTileBounds;

    QSize mSize;
    int mRows;
    int mColumns;

    std::vector<Line> mGridLines;

public:
    MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, const sf::Texture& tilesheet);

    void setCurrentTileTraversable(bool traversable);

signals:
    void clicked();
    void clicked(const Tile& tile);

public slots:
    void setCurrentTileBounds(QObject* bounds);

private slots:
    void sendSelectedTile();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
