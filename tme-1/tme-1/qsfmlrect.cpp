#include "qsfmlrect.h"

QSFMLRect::QSFMLRect(QObject* parent) :
    QObject(parent)
{

}


QSFMLRect::QSFMLRect(sf::Rect<int> rect, QObject *parent) :
    QObject(parent),
    mRect(rect)
{
}
