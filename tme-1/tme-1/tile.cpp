#include "tile.h"
#include <iostream>

Tile::Tile()
    : mTileSheetIndex(0),
      mTraversable(true)
{
}

Tile::Tile(sf::Sprite sprite, unsigned short tileSheetIndex)
    : mSprite(sprite),
      mTileSheetIndex(tileSheetIndex),
      mTraversable(true)
{
}

const sf::Sprite& Tile::getSprite() const
{
    return mSprite;
}

const sf::Vector2i& Tile::getCoords() const
{
    return mCoords;
}

const sf::Vector2i& Tile::getTileSheetCoords() const
{
    return mTileSheetCoords;
}

const sf::Vector2i& Tile::getDimensions() const
{
    return mDimensions;
}

bool Tile::getTraversable() const
{
    return mTraversable;
}

unsigned short Tile::getTileSheetIndex() const
{
    return mTileSheetIndex;
}

void Tile::setCoords(const sf::Vector2i& coords)
{
    mCoords.x = coords.x;
    mCoords.y = coords.y;
}

void Tile::setTileSheetCoords(const sf::Vector2i& tileSheetCoords)
{
    mTileSheetCoords.x = tileSheetCoords.x;
    mTileSheetCoords.y = tileSheetCoords.y;
}

void Tile::setDimensions(const sf::Vector2i& dimensions)
{
    mDimensions = dimensions;
}

void Tile::setTraversable(bool traversable)
{
    std::cout << "Tile at " << std::to_string(mCoords.x) << ", " << std::to_string(mCoords.y) << " is " << traversable << std::endl;
    mTraversable = traversable;
}
