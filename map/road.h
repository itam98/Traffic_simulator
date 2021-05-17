#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include <QDebug>
#include <QMouseEvent>


enum Side {front, back}; //used also in crossroad class

class Milestone;

class Road : public QGraphicsObject
{
    Q_OBJECT

public:
    Road(bool isCrossroad=false);
    ~Road();

    int objNo;
    static int objCnt;

    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    Milestone *mL;
    Milestone *mP;

    void connect(Road *road2, int side);


    bool isCrossroad;



protected:
    const int w=80; //width of the road


private:

    qreal speedLimit;    //przechowuje informLcje o limicie prędkości
    QPoint offset;

};

#endif // ROAD_H
