#include "sensor.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>


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
    path.addRect(-30, -120, 60, 120);
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
    foreach (Car * item, myMap->listOfCars){

        if ( collidesWithItem(item) ){
            if(item != myCar){
                value = item->getSpeed();
                myCar->setSpeed(value-1);
                qDebug() << "kolizja";
            }

        }
        else myCar->setDefaultSpeed();
    }


    return value;
}


void Sensor::setMyCar(Car* car)
{
    myCar = car;

}
