#ifndef ROUTER_H
#define ROUTER_H

#include <QGraphicsObject>
#include <QGraphicsItem>

#include <QtWidgets>
#include <QApplication>

#include "milestone.h"
#include "crossroad.h"
#include "road.h"

class Router : public QGraphicsScene
{
    Q_OBJECT

public:
    Router();


    void connect(QGraphicsScene *scene, Road *road1, Road *road2, bool inv1=false, bool inv2=false);

};

#endif // ROUTER_H
