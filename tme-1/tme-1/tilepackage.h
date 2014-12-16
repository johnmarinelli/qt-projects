#ifndef TILEPACKAGE_H
#define TILEPACKAGE_H

#include <QObject>
#include "jpushbutton.h"

/*
 * Class for mapping complex data from tile
 * selector frame to other GUI elements
 */
class TilePackage : public QObject
{
    Q_OBJECT
private:

public:
    explicit TilePackage(QObject *parent = 0);

signals:

public slots:

};

#endif // TILEPACKAGE_H
