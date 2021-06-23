#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <QGraphicsObject>
#include <QDebug>
#include "milestone.h"
#include "road.h"
#include "light.h"

enum Direction { left, straight, right};    //direction on crossroad
enum Entrance {None=-1, North=0, East=1, South=2, West=3};


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
    Light *red[4];
    Light *orange[4];
    Light *green[4];

protected:
    const int width = 100; //wielkość skrzyżowania zmienne pomconicza, później nie powinnos się jej zmieniać

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void timerEvent(QTimerEvent *event) override;

private:
    int state;
    int timer;
    bool stop_a=true;
    bool stop_b=true;
    void setLight(int a, int b);

};

#endif // CROSSROAD_H
