#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsObject>


class Sensor : public QGraphicsObject
{
    Q_OBJECT

public:
    Sensor();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    //virtual ~Sensor() {};

    //TODO: dodać sygnał wykrywający samochody


};

#endif // SENSOR_H
