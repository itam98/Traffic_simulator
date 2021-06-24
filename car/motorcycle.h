#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <QGraphicsObject>
#include "../map/milestone.h"
#include "sensor.h"
#include "map/map.h"
#include "vehicle.h"

class Sensor;
class Map;
class Vehicle;


class Motorcycle : public QGraphicsObject , public Vehicle
{
    Q_OBJECT

public:
    Motorcycle(Milestone *nextMS, Map * map);
    ~Motorcycle();
    bool faceToMilestone();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    void collision() override;

    Sensor *sensor1;
    Map* myMap;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QColor color;
    int step=0; //do debugowania sensora usun potem
    bool flag_collision = true;



};

#endif // MOTORCYCLE_H
