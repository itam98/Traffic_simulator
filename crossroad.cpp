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

    int coord[4][3]={           //x,y, rotation
        {0, -width/2 , -90},
        {width/2, 0  , 0},
        {0, width/2  , 90},
        {-width/2, 0 , 180}
    };

    for(int i=0; i<4; i++){     //create crossroad entrances
        road[i] = new Road;
        road[i]->setParentItem(this);
        road[i]->setPos(coord[i][0], coord[i][1]);
        road[i]->setRotation(coord[i][2]);
        road[i]->mA->isCrossroad = true;
    }

    for(int i=0; i<4; i++){
        int next_i = i + 1;
        if(next_i == 4) next_i = 0;

        //road[i]->mA->nextMilestone

    }

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
    else return NULL;
}

Milestone* Crossroad::getNextMilestone(Milestone* currentMilestone, Direction dir)
{
    int temp;
    for(int i=0; i<4; i++){
        if(currentMilestone == road[i]->mA)
        {
            if(dir == Direction::left) temp = i-1;
            if(dir == Direction::right) temp = i+1;
            if(dir == Direction::straight) temp = i+2;
            continue;
        }
    }

    if(temp<0) temp= temp+4;
    if(temp>3) temp=temp-4;
    return road[temp]->mB;
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


