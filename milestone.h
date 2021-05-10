#ifndef MILESTONE_H
#define MILESTONE_H

#include <QGraphicsObject>

class Milestone : public QGraphicsObject
{


public:
    Milestone();


    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    qreal getSpeedLimit();     //zwraca limit predkosci
    void setSpeedLimit(qreal value);     //ustawia limit predkosci

    Milestone *nextMilestone;    //wskaznik do nastepny punkt
    Milestone *prevMilestone;    //wskaznik do poprzedniego punkt

    private:

    qreal speedLimit;    //przechowuje informacje o limicie prędkości

};

#endif // MILESTONE_H
