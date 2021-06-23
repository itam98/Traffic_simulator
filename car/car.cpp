#include "car.h"
#include "../map/crossroad.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>

Car::Car(Milestone *nextMS, Map* map) : color(QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256))
{
    myMap = map;

    startTimer(1000/framerate);
    currentMilestone=nextMS;
    faceToMilestone();
    defaultSpeed = 30+ QRandomGenerator::global()->bounded(10);
    setSpeed(defaultSpeed);

    sensor1 = new Sensor;
    sensor1->setParentItem(this);
    sensor1->setMyCar(this);
    sensor1->myMap = this->myMap;
    sensor1->setZValue(10);

}



void Car::timerEvent(QTimerEvent *)
{
    if(currentMilestone != NULL){
        //faceToMilestone();  //dodane w każdym kroku TODO:usunąć to

        //sprawdza odległóść do obiektu
        QLineF lineToMilestone(scenePos(), currentMilestone->scenePos());
        if (lineToMilestone.length() > aproxDistanceToMS)           //sprawdź czy punkt został osiagnięty
        {
            setPos(mapToParent(0, -step_length));                   //jeśli nie to zrób krok
        }
        else                                                        //jeśli tak to pobierz nastpny punkt
        {
            if(currentMilestone->isCrossroad == false){
                currentMilestone = currentMilestone->next;
                faceToMilestone();
            }
            else{   //the car reached crossroad
                Crossroad *cross = currentMilestone->itemsCrossroad;

                int random = QRandomGenerator::global()->bounded(3);
                Milestone* milestoneFromCrossroad = NULL;
                milestoneFromCrossroad = cross->getNextMilestone(currentMilestone, (Direction)random);
                if(milestoneFromCrossroad != NULL){

                    currentMilestone = milestoneFromCrossroad;
                    faceToMilestone();

                }



            }
        }

    }

    int value = sensor1->checkSensor();
    if(value>=0){
        qDebug() << step << ": " << value;
    }
    step++;


}

QRectF Car::boundingRect() const    //OBSZAR RYSOWANIA
{
    qreal adjust = 2;
    //return QRectF(-10 - adjust, -25 - adjust,20 + adjust, 45 + adjust);
    return QRectF(-60 - adjust, -120 - adjust,120 + adjust, 180 + adjust);

}


QPainterPath Car::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    //path.addRect(-10, -25, 20, 45);
    path.addRect(-8, 0, 16, 30);
    //path.addRect(-10, -35, 20, 10);
    return path;

}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //narysuj karoserię
    painter->setBrush(color);
    painter->drawRoundedRect(-9, 0, 18, 40, 3, 3);    //(-9, -20, 18, 40, 3, 3)

    //narysuj szubę
    painter->setBrush(QColor(220,220,255));
    painter->drawRect(-8, 9, 16, 10);

    //narysuj lampy
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-9, 0, 8, 6);
    painter->drawEllipse(1, 0, 8, 6);

}

bool Car::faceToMilestone()     //skieruj samochód w kierunku następnego celu
{
    if(currentMilestone != NULL){
        //tworzy liczbę zepoloną
        std::complex<double> temp(  currentMilestone->scenePos().x()-x()  ,  -(currentMilestone->scenePos().y()-y())  ); //tworzy liczbę zepoloną
        qreal angle = qRadiansToDegrees(  std::arg(temp)  );    //zwraca kat powyższej liczby
        setTransform(QTransform().rotate(90-angle), false);
        return true;
    }
    else return false;

}



