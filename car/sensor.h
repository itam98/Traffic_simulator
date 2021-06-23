#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsObject>
#include "car.h"
#include "motorcycle.h"
#include "map/map.h"

class Car;
class Motorcycle;
class Map;


class Sensor : public QGraphicsObject
{
    Q_OBJECT

public:
    Sensor();


    void setMyCar(Car* car);
    void setMyMotor(Motorcycle* motor);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    int checkSensor();  //zwraca prędkość wykrytego pojazd z przodu



    Map * myMap;

    //virtual ~Sensor() {};

    //TODO: dodać sygnał wykrywający samochody

    private:

        Car* myCar = NULL;
        Motorcycle* myMotor = NULL;


};

#endif // SENSOR_H
