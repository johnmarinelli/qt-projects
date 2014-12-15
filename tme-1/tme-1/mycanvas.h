#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "qsfmlrect.h"
#include "Vector2d.h"

#include <iostream>
#include <unordered_map>
#include <QMouseEvent>

/*
 * custom comparator for comparing two 2d vectors
 * note that std::map comparators assume you fulfill the following axioms
 * irreflexive, asymmetric, transitive
 *
 * A strict weak ordering has the following properties. For all x and y in S,
 * For all x, it is not the case that x < x (irreflexivity).
 * For all x, y, if x < y then it is not the case that y < x (asymmetry).
 * For all x, y, and z, if x < y and y < z then x < z (transitivity).
 * For all x, y, and z, if x is incomparable with y, and y is incomparable with z,
 * then x is incomparable with z (transitivity of incomparability).
 *
 * so cmp(a,b) = false and cmp(b,a) = true then a, b aren't equal.
 */
struct Vector2iComparator
        : public std::binary_function<sf::Vector2i, sf::Vector2i, bool> {
    bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
        bool retval = false;
        if(a.x < b.x || a.y > b.y) {
            retval = true;
        }
        /*if(a.y < b.y) {
            retval = true;
        }*/

        if(retval) {
            std::cout << "a.x: " << a.x << std::endl;
            std::cout << "a.y: " << a.y << std::endl;
            std::cout << "\n";
            std::cout << "b.x: " << b.x << std::endl;
            std::cout << "b.y: " << b.y << std::endl;
            std::cout << "_------------_" << std::endl;
        }

        return retval;
    }
};

/*
 * functor to hash keys
 */
struct Vector2iHash {
    std::size_t operator()(const sf::Vector2i& key) const {
        return std::hash<int>()(key.x ^ (std::hash<int>()(key.y) << 1) >> 1);
    }
};

struct Vector2iKeyEqual {
    bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

class MyCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();

    sf::Texture mTilesheet;
    std::map<sf::Vector2i, sf::Sprite, Vector2iComparator> mTiles;

    std::unordered_map<sf::Vector2i, sf::Sprite, Vector2iHash> mTiles2;

    sf::Sprite mSprite;

    sf::Rect<int> mCurrentTileBounds;

    QSize mSize;

public:
    MyCanvas(QWidget *parent, const QPoint& position, const QSize& size, sf::Texture& tilesheet);

signals:

public slots:
    void setCurrentTileBounds(QObject* bounds);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
