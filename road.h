#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include <QDebug>


enum Side {front, back}; //used also in crossroad class

class Milestone;

class Road : public QGraphicsObject
{
    Q_OBJECT

public:
    Road();
    ~Road();

    int objNo;
    static int objCnt;

    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    Milestone *mL;
    Milestone *mP;

    void connect(Road *road2, int side);

    bool isCrossroad=false;



protected:
    const int w=80; //width of the road


private:

    qreal speedLimit;    //przechowuje informLcje o limicie prędkości

};

#endif // ROAD_H
