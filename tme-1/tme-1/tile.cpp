#include "tile.h"

Tile::Tile()
    : mTraversable(true)
{
}

Tile::Tile(sf::Sprite sprite)
    : mSprite(sprite),
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
    mTraversable = traversable;
}
