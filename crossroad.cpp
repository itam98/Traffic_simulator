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
        road[i]->mL->isCrossroad = true;
        road[i]->mL->itemsCrossroad = this;
    }

    //road[i]->mL->isCrossroad

    for(int i=0; i<4; i++){
        int next_i = i + 1;
        if(next_i == 4) next_i = 0;

        //road[i]->mL->nextMilestone

    }




}

Road* Crossroad::getEntrance(Entrance entrance)
{
    if(entrance==Entrance::North) return road[Entrance::North];
    else if(entrance==Entrance::East) return road[Entrance::East];
    else if(entrance==Entrance::South) return road[Entrance::South];
    else if(entrance==Entrance::West) return road[Entrance::West];
    else return NULL;
}

Milestone* Crossroad::getNextMilestone(Milestone* currentMilestone, Direction dir)
{

    int temp;

    for(int i=0; i<4; i++){
        if(currentMilestone == road[i]->mL)
        {
            if(dir == Direction::left) temp = i+1;
            if(dir == Direction::right) temp = i-1;
            if(dir == Direction::straight) temp = i+2;
        }

    }

    if(temp<0) temp= temp+4;
    if(temp>3) temp=temp-4;
    return road[temp]->mP;
}







QRectF Crossroad::boundingRect() const    //obszar rysowania
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
    painter->setBrush(QColor(0, 0, 0));
    painter->drawRect(-width/2, -width/2, width, width);


}


