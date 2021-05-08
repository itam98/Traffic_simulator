#include "milestone.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>

Milestone::Milestone()
{

}


QRectF Milestone::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-5 - adjust, -5 - adjust,
                  10 + adjust, 10 + adjust);
}


QPainterPath Milestone::shape() const
{
    QPainterPath path;
    path.addRect(-5, -5, 10, 10);
    return path;
}

void Milestone::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::yellow);      //narysuj kropkę w celu debugowania
    painter->drawEllipse(-3, -3, 6, 6); //TODO:wyłączyć to w ostecznej wersji programu
}


void Milestone::setSpeedLimit(qreal value)
{
    //TODO: weyfikacja podanej wartości
    speedLimit = value;
}


qreal Milestone::getSpeedLimit(){
    return speedLimit;
}

