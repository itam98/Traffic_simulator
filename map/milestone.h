#ifndef MILESTONE_H
#define MILESTONE_H

#include <QGraphicsObject>
#include "crossroad.h"
#include "road.h"


class Crossroad;
class Road;

class Milestone : public QGraphicsObject
{
    Q_OBJECT

public:
    Milestone();



    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    qreal getSpeedLimit();     //zwraca limit predkosci
    void setSpeedLimit(qreal value);     //ustawia limit predkosci

    Milestone *next;    //wskaznik do nastepny punkt
    Milestone *prev;    //wskaznik do poprzedniego punkt

    Road *itemsRoad;
    Crossroad *itemsCrossroad;

    bool isCrossroad=false;

    private:

    qreal speedLimit;    //przechowuje informacje o limicie prędkości

};

#endif // MILESTONE_H
