#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include <QDebug>

enum Side { North=0, East=1, South=2, West=3, front, back}; //used also in crossroad class

class Road : public QGraphicsObject
{
    Q_OBJECT

public:
    Road();

    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    Milestone *mA;
    Milestone *mB;

    void connect(Road *road2, int side);

    bool isCrossroad=false;

protected:
    const int w=80; //width of the road

private:

    qreal speedLimit;    //przechowuje informacje o limicie prędkości

};

#endif // ROAD_H
