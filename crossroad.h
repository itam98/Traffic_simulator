#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include "road.h"

enum Direction { left, straight, right};    //direction on crossroad
enum Entrance {North, East, South, West};


class Milestone;
class Road;

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

    Road *getEntrance(Entrance entrance);


    Road *road[4];


protected:
    const int width = 100; //wielkość skrzyżowania zmienne pomconicza, później nie powinnos się jej zmieniać

private:

};

#endif // CROSSROAD_H
