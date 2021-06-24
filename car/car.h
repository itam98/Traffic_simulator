#ifndef CAR_H
#define CAR_H

#include <QGraphicsObject>
#include "../map/milestone.h"
#include "sensor.h"
#include "map/map.h"
#include "vehicle.h"

class Sensor;
class Map;
class Vehicle;

class Car : public QGraphicsObject , public Vehicle
{
    Q_OBJECT

public:
    Car(Milestone *nextMS, Map * map);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    bool faceToMilestone();
    void collision() override;
    Sensor *sensor1;
    Map* myMap;


protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QColor color;
    int step=0; //do debugowania sensora usun potem
};

#endif // CAR_H
