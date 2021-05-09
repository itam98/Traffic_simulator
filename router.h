#ifndef ROUTER_H
#define ROUTER_H

#include <QGraphicsObject>
#include "milestone.h"
#include "crossroad.h"
#include "road.h"

class Router : public QObject
{
    Q_OBJECT

public:
    Router();


    void connect(Road *road1, Road *road2, bool inv1=false, bool inv2=false);

};

#endif // ROUTER_H
