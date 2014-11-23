#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <SFML/Graphics.hpp>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
private:
    virtual void OnInit();

    virtual void OnUpdate();

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent* e);

    virtual void paintEvent(QPaintEvent* e);

    QTimer mTimer;
    bool mInitialized;

public:
    explicit QSFMLCanvas(QWidget *parent, const QPoint& position, const QSize& size, unsigned int frametime = 0);

    virtual ~QSFMLCanvas();

signals:

public slots:

};

#endif // QSFMLCANVAS_H
