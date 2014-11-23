#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget *parent, const QPoint &position, const QSize &size, unsigned int frametime) :
    QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    move(position);
    resize(size);

    mTimer.setInterval(frameTime);
}

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

void QSFMLCanvas::showEvent(QShowEvent* e)
{
    if(!mInitialized)
    {
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        Create(winId());

        OnInit();

        connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        mTimer.start();
        mInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent* e)
{
    OnUpdate();
    Display();
}
