#ifndef JPUSHBUTTON_H
#define JPUSHBUTTON_H

#include <QPushButton>
#include <SFML/Graphics.hpp>

class JPushButton : public QPushButton
{
    Q_OBJECT
private:
    sf::Rect<int> mClipBounds;

public:
    explicit JPushButton(QWidget* parent = 0);

    void setClipBounds(int top, int left, int width, int height);
    sf::Rect<int> getClipBounds();

signals:

public slots:

};

#endif // JPUSHBUTTON_H
