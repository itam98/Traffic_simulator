#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include <QDebug>

enum Side { front, back, North, East, South, West}; //used also in crossroad class

class Road : public QGraphicsObject
{
    Q_OBJECT

public:
    Road();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    Milestone *mA;
    Milestone *mB;

    void connect(Road *road2, int side);

protected:
    const int w=80; //width of the road

private:

        qreal speedLimit;    //przechowuje informacje o limicie prędkości

};

#endif // ROAD_H
