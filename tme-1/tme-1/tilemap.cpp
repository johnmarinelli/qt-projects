#include "tilemap.h"
#include <QFile>
#include <iostream>
#include <QTextStream>

TileMap::TileMap()
{
}

TileMap::TileMap(int tileWidth,
                 int tileHeight,
                 int width,
                 int height) :
    mTileWidth(tileWidth),
    mTileHeight(tileHeight),
    mWidth(width),
    mHeight(height)
{
}

int TileMap::getTileWidth() const
{
    return mTileWidth;
}

int TileMap::getTileHeight() const
{
    return mTileHeight;
}

int TileMap::getWidth() const
{
    return mWidth;
}

int TileMap::getHeight() const
{
    return mHeight;
}

void TileMap::setTileWidth(int tileWidth)
{
    mTileWidth = tileWidth;
}

void TileMap::setTileHeight(int tileHeight)
{
    mTileHeight = tileHeight;
}

void TileMap::setWidth(int width)
{
    mWidth = width;
}

void TileMap::setHeight(int height)
{
    mHeight = height;
}

void TileMap::addTile(const Tile &tile)
{
    mTiles.push_back(&tile);
}

void TileMap::removeTile(const Tile *other)
{
    const Tile* remove = nullptr;
    for(const auto& t : mTiles) {
        if(t == other) {
            remove = t;
        }
    }
    mTiles.erase(std::remove(mTiles.begin(), mTiles.end(), remove));
}

void TileMap::saveMap(const QString& path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text )) {
        std::cout << "Unable to open " << path.toStdString() << " for writing. " << std::endl;
        return;
    }

    QTextStream output(&file);
    output << "Sup" << "\n";
}

void TileMap::reset()
{
    mTileWidth = 0;
    mTileHeight = 0;
    mWidth = 0;
    mHeight = 0;
    mTiles.clear();
}
