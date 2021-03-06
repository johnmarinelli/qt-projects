#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "line.h"
#include "tile.h"
#include "tilesheethandler.h"
#include "tilemap.h"

#include <iostream>
#include <unordered_map>
#include <QMouseEvent>
#include <memory>

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

    typedef std::unordered_map<sf::Vector2<int>, Tile, Vector2iHash> TilesMap;

    sf::Texture mTilesheet;
    TilesMap mTiles;

    /*
     * Canvas needs a reference to TileSheetHandler to determine
     * which tilesheet to use when drawing tiles.
     */
    const TileSheetHandler& mTileSheetHandler;
    unsigned short mTileSheetIndex;

    Tile* mSelectedTile;

    sf::Rect<int> mCurrentTileBounds;

    std::vector<Line> mGridLines;

    TileMap mTileMap;

public:
    MyCanvas(QWidget *parent,
             const QPoint& position,
             const QSize& size,
             const TileSheetHandler& tileSheetHandler,
             const int tileWidth,
             const int tileHeight);

    void setLines();
    void setCurrentTileTraversable(bool traversable);
    void reset();
    void setTileDimensions(int tileWidth, int tileHeight);
    void setDimensions(int width, int height);

    void saveMap(const QString& path);

    QSize sizeHint() const;

    ~MyCanvas();

signals:
    void clicked();
    void clicked(const Tile& tile);

public slots:
    void setCurrentTile(const sf::Rect<int>& bounds, const std::shared_ptr<const TileSheet> tileSheet);
    void setCurrentTileSheetIndex(int index);

private slots:
    void sendSelectedTile();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
