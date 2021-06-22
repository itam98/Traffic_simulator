#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsObject>
#include "car.h"
#include "map/map.h"

class Car;
class Map;

class Sensor : public QGraphicsObject
{
    Q_OBJECT

public:
    Sensor();




    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    int checkSensor();  //zwraca prędkość wykrytego pojazd z przodu

    void setMyCar(Car* car);

    Map * myMap;

    //virtual ~Sensor() {};

    //TODO: dodać sygnał wykrywający samochody

    private:

        Car* myCar;


};

#endif // SENSOR_H
