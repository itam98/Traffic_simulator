#include "road.h"

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPainter>
#include <QStyleOption>
#include <qmath.h>


Road::Road()
{
    //A
    //x
    //B

    //Milestone *mA = new Milestone;
    //Milestone *mB = new Milestone;

    mA = new Milestone;
    mB = new Milestone;

    mA->setParentItem(this);
    mA->setPos(0,-w/4);

    mB->setParentItem(this);
    mB->setPos(0,w/4);
}


QRectF Road::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-5 - adjust, -30 - adjust,
                  10 + adjust, 60 + adjust);
}


QPainterPath Road::shape() const
{
    QPainterPath path;
    path.addRect(-2, -30, 11, 60);
    return path;
}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(Qt::black);
    //painter->drawRect(-2, -25, 4, 50);
    painter->drawLine(0, -w/2, 0, w/2);
    painter->drawLine(-2, -w/2, 2, -w/2);
    painter->drawLine(-2, w/2, 2, w/2);

    painter->setBrush(Qt::green);
    //painter->drawEllipse(-2, -2, 4, 4);

    painter->setBrush(Qt::black);
    painter->drawLine(0, -4, 9, 0);
    painter->drawLine(0, 4, 9, 0);

}



