#ifndef CAR_H
#define CAR_H

#include <QGraphicsObject>
#include "../map/milestone.h"
#include "sensor.h"
#include "map/map.h"

class Sensor;
class Map;

class Car : public QGraphicsObject
{
    Q_OBJECT

public:
    Car(Milestone *nextMS, Map * map);

    qreal framerate = 60; //ilość kroków symulacji na sekundę

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    bool faceToMilestone();
    void setMilestone(Milestone *nextMS);

    void setSpeed(qreal value);
    qreal getSpeed();

    Sensor *sensor1;
    Map* myMap;

    void setDefaultSpeed();

protected:
    void timerEvent(QTimerEvent *event) override;
    qreal defaultSpeed;

private:
    qreal direction = 0;
    qreal speed = 0;
    qreal step_length = 0;
    QColor color;
    Milestone *currentMilestone;
    int aproxDistanceToMS;

    int step=0; //do debugowania sensora usun potem
};

#endif // CAR_H
