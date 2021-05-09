#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <QGraphicsObject>
#include "milestone.h"
#include "road.h"


class Crossroad : public QGraphicsObject
{
    Q_OBJECT

public:
    Crossroad();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;



    Road *entrance_N;   //   N
    Road *entrance_E;   // W + E
    Road *entrance_S;   //   S
    Road *entrance_W;

    Road* getEntrance(Side side);

protected:
    const int width = 100; //wielkość skrzyżowania zmienne pomconicza, później nie powinnos się jej zmieniać

private:

};

#endif // CROSSROAD_H
