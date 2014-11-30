#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include <QMouseEvent>

class MyCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();

    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Image mImage;

    std::string mCurrentTileName;

public:
    MyCanvas(QWidget *parent, const QPoint& position, const QSize& size);

signals:

public slots:
    void setCurrentTileName(QString name);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYCANVAS_H
