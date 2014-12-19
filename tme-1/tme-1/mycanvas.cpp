#include "mycanvas.h"
#include "utility.h"
#include <iostream>
#include <sstream>

MyCanvas::MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, const sf::Texture& tilesheet) :
    QSFMLCanvas(parent, position, size),
    mTilesheet(tilesheet),
    mSize(size),
    mColumns(std::ceil(size.width() / TILE_WIDTH)),
    mRows(std::ceil(size.height() / TILE_HEIGHT)),
    mSelectedTile(nullptr)
{
    /* vertical lines */
    for(int i = 0; i < mColumns; ++i) {
        int x = i * TILE_WIDTH;
        Line line(x, 0, x, size.height());
        line.mLine[0].color = sf::Color::Black;
        mGridLines.push_back(line);
    }

    /* horizontal lines */
    for(int j = 0; j < mRows; ++j) {
        int y = j * TILE_WIDTH;
        Line line(0, y, size.width(), y);
        line.mLine[0].color = sf::Color::Black;
        mGridLines.push_back(line);
    }

    /* remap our normal clicked() function to our slot, sendSelectedTile */
    connect(this, SIGNAL(clicked()), this, SLOT(sendSelectedTile()));
}


void MyCanvas::sendSelectedTile()
{
    /* then sendSelectedTile() will emit a different signal that passes an argument */
    if(mSelectedTile) emit clicked(*mSelectedTile);
}

void MyCanvas::onInit()
{
}

void MyCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color(255, 255, 255));

    for(const auto& line : mGridLines) {
        draw(line.mLine, 2, sf::Lines);
    }

    for(const auto& tile : mTiles) {
        draw(tile.second.getSprite());
    }
}

void MyCanvas::setCurrentTileBounds(QObject* bounds)
{
    QRect r = bounds->property("bounds").toRect();

    mCurrentTileBounds.left = r.left();
    mCurrentTileBounds.top = r.top();
    mCurrentTileBounds.width = r.width();
    mCurrentTileBounds.height = r.height();
}

void MyCanvas::setCurrentTileTraversable(bool traversable)
{
    if(mSelectedTile) mSelectedTile->setTraversable(traversable);
}

void MyCanvas::mousePressEvent(QMouseEvent* event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    x = getNearestMultiple(x, TILE_WIDTH);
    y = getNearestMultiple(y, TILE_HEIGHT);

    sf::Vector2i coords(x, y);

    /* find tile */
    auto tile = mTiles.find(coords);

    if(event->button() & Qt::LeftButton) {
        /* place tile at snapped point */
        sf::Sprite sprite;

        sprite.setTexture(mTilesheet);
        sprite.setTextureRect(mCurrentTileBounds);

        sprite.setPosition(x, y);
        Tile tile(sprite);
        tile.setCoords(sf::Vector2i(x, y));
        tile.setTileSheetCoords(sf::Vector2i(mCurrentTileBounds.left, mCurrentTileBounds.top));
        tile.setDimensions(sf::Vector2i(TILE_WIDTH, TILE_HEIGHT));

        mTiles[coords] = tile;
        mSelectedTile = &(mTiles[coords]);
    }

    else if(event->button() & Qt::RightButton) {
        /* delete tile */
        if(tile != mTiles.end()) {
            //mTiles.erase(tile);
            mSelectedTile = &(tile->second);
        }
    }

    emit clicked();
}
