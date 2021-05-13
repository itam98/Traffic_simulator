#include "road.h"

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPainter>
#include <QStyleOption>
#include <qmath.h>

#include <QtWidgets>

int Road::objCnt;

Road::Road()
{
    //L A   TODO: zmienić A i B na L i P
    //x>
    //P B
    objNo = ++objCnt;


    mL = new Milestone;
    mP = new Milestone;

    mL->setParentItem(this);
    mL->setPos(0,-w/4);

    mP->setParentItem(this);
    mP->setPos(0,w/4);

    mL->itemsRoad = this;
    mP->itemsRoad = this;
}

Road::~Road()
{
--objCnt;
}

QRectF Road::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-5 - adjust, -50 - adjust,
                  10 + adjust, 80 + adjust);
}


/*QPainterPath Road::shape() const
{
    QPainterPath path;
    path.addRect(-2, -30, 11, 60);
    return path;
}*/

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
    QString s = QString::number(objNo);
    painter->drawText(0,-50, s);

}




