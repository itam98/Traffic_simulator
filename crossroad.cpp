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


    rNorth = new Road;
    rEast = new Road;
    rSouth = new Road;
    rWest = new Road;

    rNorth->setParentItem(this);
    rEast->setParentItem(this);
    rSouth->setParentItem(this);
    rWest->setParentItem(this);

    rNorth->setPos(0, -width/2);
    rNorth->setRotation(-90);
    rEast->setPos(width/2, 0);
    rSouth->setPos(0, width/2);
    rSouth->setRotation(90);
    rWest->setPos(-width/2, 0);
    rWest->setRotation(180);


    //
    rNorth->mA->nextMilestone = rWest->mB;
    rWest->mB->prevMilestone = rNorth->mA;

    rWest->mA->nextMilestone = rNorth->mB;
    rNorth->mB->prevMilestone = rWest->mA;

}

Road* Crossroad::getEntrance(Side side)
{
    if(side==Side::North) return rNorth;
    else if(side==Side::East) return rEast;
    else if(side==Side::South) return rSouth;
    else if(side==Side::West) return rWest;
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
