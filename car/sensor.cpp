#include "sensor.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>
#include <qmath.h>

Sensor::Sensor()
{

}


/**********************************************
 *  Obszar rysowania obiektu
 */
QRectF Sensor::boundingRect() const    //metoda dziedziczona po wirtualnej metodzie w graphicsobject a dokładniej grpahicsItem
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -25 - adjust,20 + adjust, 45 + adjust);

}

/**********************************************
 *  Kształt obiektu służący do wykrywania kolizji
 */
QPainterPath Sensor::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    path.addRect(-30, -100, 60, 120);
    return path;

}

/**********************************************
 *  Funkcja rysująca obiekt
 */
void Sensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(QColor(200,50,50,90));
    painter->setPen(Qt::NoPen);

    static const QPointF points[4] = {
        QPointF(0.0, 0.0),
        QPointF(-30.0, -60.0),
        QPointF(30.0, -60.0)
    };

    painter->drawPolygon(points, 3);

}

/**********************************************
 *  Odczytuje stan sensora, sprawdza czy nie wykryto auta
 */
int Sensor::checkSensor()
{
    int value = -1;
    if (myCar == NULL){
        foreach (Car * item, myMap->listOfCars){

            if ( collidesWithItem(item) ){

                    value = item->getSpeed();
                    myMotor->collision(); //loor(value*0.98)
                    qDebug() << "kolizja MOTOCYKLA";
                    cnt=0;
            }
            else{

                if(cnt++ >5){
                    myMotor->setDefaultSpeed();

                }
            }
        }
    }
    else{
        foreach (Car * item, myMap->listOfCars){

            if ( collidesWithItem(item) ){
                if(item != myCar){
                    value = item->getSpeed();
                    myCar->collision(); //loor(value*0.98)
                    qDebug() << "kolizja";
                    cnt=0;
                }

            }
            else{
                if(cnt++ >5) myCar->setDefaultSpeed();

            }
        }
    }

    return value;
}

/**********************************************
 *  Ustawia wzkaźnik do samochodu na którym jest "zamontowany"
 */
void Sensor::setMyCar(Car* car)
{
    myCar = car;

}

/**********************************************
 *  Ustawia wzkaźnik do motocyklu na którym jest "zamontowany"
 */
void Sensor::setMyMotor(Motorcycle* motor)
{
    myMotor = motor;

}


