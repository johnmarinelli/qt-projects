#include "tilemap.h"

#include "json/json.h"

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

    /* root level for tile map */
    Json::Value tileMapRoot;

    /* nested value for tiles */
    Json::Value tiles = Json::Value(Json::arrayValue);

    for(const auto& t : mTiles) {
        /* create tile object */
        Json::Value tile;

        /* prepare raw values to be put in json format */
        sf::Vector2i worldCoords = t->getCoords();
        int x = worldCoords.x;
        int y = worldCoords.y;

        sf::Vector2i tileSheetCoords = t->getTileSheetCoords();
        int sX = tileSheetCoords.x;
        int sY = tileSheetCoords.y;

        bool traversable = t->getTraversable();

        Json::Value worldCoordsJSON = Json::Value(Json::arrayValue);
        Json::Value tileSheetCoordsJSON = Json::Value(Json::arrayValue);
        Json::Value traversableJSON = traversable;

        /* fill up json values */
        worldCoordsJSON.append(x);
        worldCoordsJSON.append(y);

        tileSheetCoordsJSON.append(sX);
        tileSheetCoordsJSON.append(sY);

        /* add JSON values to tile */
        tile["worldCoords"] = worldCoordsJSON;
        tile["tileSheetCoords"] = tileSheetCoordsJSON;
        tile["isTraversable"] = traversableJSON;

        /* add tile object to tiles array */
        tiles.append(tile);
    }

    tileMapRoot["tiles"] = tiles;

    /* write to file */
    Json::StyledWriter writer;
    std::string JSONOutput = writer.write(tileMapRoot);

    output << JSONOutput.c_str();
}

void TileMap::reset()
{
    mTileWidth = 0;
    mTileHeight = 0;
    mWidth = 0;
    mHeight = 0;
    mTiles.clear();
}
