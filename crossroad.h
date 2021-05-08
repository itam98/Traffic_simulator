#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <QGraphicsObject>
#include "milestone.h"

class Crossroad : public QGraphicsObject
{
    Q_OBJECT

public:
    Crossroad(QGraphicsScene* scene, int x, int y, Milestone* eN, Milestone* eE, Milestone* eS, Milestone* eW);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    Milestone entrance_N;   //   N
    Milestone entrance_E;   // W + E
    Milestone entrance_S;   //   S
    Milestone entrance_W;

    Milestone* getEntrance_N();

protected:
    const int width = 120; //wielkość skrzyżowania zmienne pomconicza, później nie powinnos się jej zmieniać

private:

};

#endif // CROSSROAD_H
