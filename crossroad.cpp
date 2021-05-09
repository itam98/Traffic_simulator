#include "crossroad.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>


Crossroad::Crossroad()
{

    //   N
    // W + E
    //   S

    //setPos(x,y);

    entrance_N = new Road;
    entrance_E = new Road;
    entrance_S = new Road;
    entrance_W = new Road;

    entrance_N->setParentItem(this);
    entrance_E->setParentItem(this);
    entrance_S->setParentItem(this);
    entrance_W->setParentItem(this);

    entrance_N->setPos(0, -width/2);
    entrance_N->setRotation(-90);
    entrance_E->setPos(width/2, 0);
    entrance_S->setPos(0, width/2);
    entrance_S->setRotation(90);
    entrance_W->setPos(-width/2, 0);
    entrance_W->setRotation(180);

    entrance_N->mA->nextMilestone = entrance_W->mB;
    entrance_W->mB->prevMilestone = entrance_N->mA;

    entrance_W->mA->nextMilestone = entrance_N->mB;
    entrance_N->mB->prevMilestone = entrance_W->mA;

}

Road* Crossroad::getEntrance(Side side)
{
    if(side==Side::North) return entrance_N;
    else if(side==Side::East) return entrance_E;
    else if(side==Side::South) return entrance_S;
    else if(side==Side::West) return entrance_W;
    else return 0;
}


QRectF Crossroad::boundingRect() const    //metoda dziedziczona po wirtualnej metodzie w graphicsobject a dokładniej grpahicsItem
{
    qreal adjust = 0.5;
    return QRectF(-width/2 - adjust, -width/2 - adjust,
                  width + adjust, width + adjust);
}


QPainterPath Crossroad::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    path.addRect(-width/2, -width/2, width, width);
    return path;
}

void Crossroad::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(145, 127, 87));
    painter->drawRect(-width/2, -width/2, width, width);


}
