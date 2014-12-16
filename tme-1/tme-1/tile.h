#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

/*
 * class for physica representation of tile
 */
class Tile
{
private:
    sf::Sprite mSprite;

    /* map coordinates */
    sf::Vector2i mCoords;

    /* coordinates on tile sheet */
    sf::Vector2i mTileSheetCoords;

    sf::Vector2i mDimensions;

    bool mTraversable;

public:
    Tile();
    explicit Tile(sf::Sprite sprite);
    /*
     * TODO:
     * move semantics
     */

    const sf::Sprite& getSprite() const;
    const sf::Vector2i& getCoords() const;
    const sf::Vector2i& getTileSheetCoords() const;
    const sf::Vector2i& getDimensions() const;

    void setCoords(const sf::Vector2i& coords);
    void setTileSheetCoords(const sf::Vector2i& tileSheetCoords);
    void setDimensions(const sf::Vector2i& dimensions);
    void setTraversable(bool traversable);

};

#endif // TILE_H
