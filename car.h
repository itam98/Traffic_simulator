#ifndef CAR_H
#define CAR_H

#include <QGraphicsObject>
#include "milestone.h"
#include "sensor.h"

class Car : public QGraphicsObject
{
    Q_OBJECT

public:
    Car(Milestone *nextMS);

    qreal framerate = 60; //ilość kroków symulacji na sekundę

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    void faceToMilestone();
    void setMilestone(Milestone *nextMS);

    void setSpeed(qreal value);
    qreal getSpeed();

    Sensor *sensor1;

protected:
    void timerEvent(QTimerEvent *event) override;
    qreal defaultSpeed;

private:
    qreal direction = 0;
    qreal speed = 0;
    qreal step_length = 0;
    QColor color;
    Milestone *nextMilestone;
    int aproxDistanceToMS;
};

#endif // CAR_H
