#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

/*
 * class for physical representation of tile
 */
class Tile
{
private:
    sf::Sprite mSprite;

    /* map coordinates */
    sf::Vector2i mCoords;

    /* index for TileSheetHandler */
    unsigned short mTileSheetIndex;

    /* coordinates on tile sheet */
    sf::Vector2i mTileSheetCoords;

    sf::Vector2i mDimensions;

    bool mTraversable;

public:
    Tile();
    explicit Tile(sf::Sprite sprite, unsigned short tileSheetIndex);
    /*
     * TODO:
     * move semantics
     */

    const sf::Sprite& getSprite() const;
    const sf::Vector2i& getCoords() const;
    const sf::Vector2i& getTileSheetCoords() const;
    const sf::Vector2i& getDimensions() const;
    bool getTraversable() const;
    unsigned short getTileSheetIndex() const;

    void setCoords(const sf::Vector2i& coords);
    void setTileSheetCoords(const sf::Vector2i& tileSheetCoords);
    void setDimensions(const sf::Vector2i& dimensions);
    void setTraversable(bool traversable);

};

#endif // TILE_H
