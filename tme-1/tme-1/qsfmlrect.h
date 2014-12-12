#ifndef QSFMLRECT_H
#define QSFMLRECT_H

#include <QObject>
#include <SFML/Graphics/Rect.hpp>

class QSFMLRect : public QObject
{
    Q_OBJECT
public:
    QSFMLRect(QObject* parent=nullptr);
    QSFMLRect(sf::Rect<int> rect, QObject *parent = 0);
    QSFMLRect(const QSFMLRect& rect) {};

    sf::Rect<int> mRect;

signals:

public slots:

};

#endif // QSFMLRECT_H
