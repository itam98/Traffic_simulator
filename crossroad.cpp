#include "crossroad.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>


Crossroad::Crossroad(QGraphicsScene* scene, int x, int y, Milestone* eN, Milestone* eE, Milestone* eS, Milestone* eW)
{

    //   N
    // W + E
    //   S

    setPos(x,y);

    entrance_N.setPos(x-width/4,y-width/2);
    entrance_E.setPos(x+width/2,y-width/4);
    entrance_S.setPos(x+width/4,y+width/2);
    entrance_W.setPos(x-width/2,y+width/4);

    entrance_N.nextMilestone=&entrance_W;
    entrance_W.nextMilestone=eW;

    scene->addItem(this);
    scene->addItem(&entrance_N);
    scene->addItem(&entrance_E);
    scene->addItem(&entrance_S);
    scene->addItem(&entrance_W);

}

Milestone* Crossroad::getEntrance_N()
{
    return &entrance_N;
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
