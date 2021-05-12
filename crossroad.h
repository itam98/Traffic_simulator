#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include "road.h"

enum Direction { left=1, straight=2, right=3};    //direction on crossroad

class Crossroad : public QGraphicsObject
{
    Q_OBJECT

public:
    Crossroad();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    Milestone* getNextMilestone(Milestone* currentMilestone, Direction dir);

    Road *rNorth;  //   N
    Road *rEast;   // W + E
    Road *rSouth;  //   S
    Road *rWest;

    Road *road[4];

    Road* getEntrance(Side side);



protected:
    const int width = 100; //wielkość skrzyżowania zmienne pomconicza, później nie powinnos się jej zmieniać

private:

};

#endif // CROSSROAD_H
