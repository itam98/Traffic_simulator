#include "sensor.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>
#include <qmath.h>

Sensor::Sensor()
{

}



QRectF Sensor::boundingRect() const    //metoda dziedziczona po wirtualnej metodzie w graphicsobject a dokładniej grpahicsItem
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -25 - adjust,20 + adjust, 45 + adjust);

}


QPainterPath Sensor::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    path.addRect(-30, -100, 60, 120);
    return path;

}

void Sensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(QColor(200,50,50,90));
    painter->setPen(Qt::NoPen);

    static const QPointF points[4] = {
        QPointF(0.0, -20.0),
        QPointF(-30.0, -120.0),
        QPointF(30.0, -120.0)
    };

    painter->drawPolygon(points, 3);

}

int Sensor::checkSensor()
{
    int value = -1;
    qDebug() << "yay";
    if (myCar == NULL){
        foreach (Car * item, myMap->listOfCars){

            if ( collidesWithItem(item) ){

                    value = item->getSpeed();
                    myMotor->setSpeed( 0 ); //loor(value*0.98)
                    qDebug() << "kolizja";


            }
            else myMotor->setDefaultSpeed();
        }
    }
    else{
        foreach (Car * item, myMap->listOfCars){

            if ( collidesWithItem(item) ){
                if(item != myCar){
                    value = item->getSpeed();
                    myCar->setSpeed( 0 ); //loor(value*0.98)
                    qDebug() << "kolizja";
                }

            }
            else myCar->setDefaultSpeed();
        }
    }

    return value;
}


void Sensor::setMyCar(Car* car)
{
    myCar = car;

}

void Sensor::setMyMotor(Motorcycle* motor)
{
    myMotor = motor;

}


