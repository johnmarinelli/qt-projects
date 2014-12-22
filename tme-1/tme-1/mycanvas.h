#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "qsfmlrect.h"
#include "line.h"
#include "tile.h"
#include "tilesheethandler.h"

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
    typedef std::map<unsigned short, TilesMap> TileSheetsMap;

    sf::Texture mTilesheet;
    std::unordered_map<sf::Vector2i, Tile, Vector2iHash> mTiles;

    const TileSheetHandler& mTileSheetHandler;
    TileSheetsMap mTileSheets;
    unsigned short mTileSheetIndex;

    Tile* mSelectedTile;

    sf::Rect<int> mCurrentTileBounds;

    QSize mSize;
    int mRows;
    int mColumns;

    std::vector<Line> mGridLines;

public:
    MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, const TileSheetHandler& tileSheetHandler);

    void setCurrentTileTraversable(bool traversable);

signals:
    void clicked();
    void clicked(const Tile& tile);

public slots:
    void setCurrentTileBounds(QObject* bounds);
    void setCurrentTile(const sf::Rect<int>& bounds, std::shared_ptr<const TileSheet> tileSheet);
    void setCurrentTileSheetIndex(int index);

private slots:
    void sendSelectedTile();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
