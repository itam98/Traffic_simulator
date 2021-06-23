#include "motorcycle.h"
#include "../map/crossroad.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>


Motorcycle::Motorcycle(Milestone *nextMS, Map* map) : color(QRandomGenerator::global()->bounded(256),
                                                            QRandomGenerator::global()->bounded(256),
                                                            QRandomGenerator::global()->bounded(256))
{
    myMap = map;
    qDebug() << "--- 1 ---";
    startTimer(1000/framerate);
    currentMilestone=nextMS;
    faceToMilestone();
    defaultSpeed = 50+ QRandomGenerator::global()->bounded(100);
    setSpeed(defaultSpeed);

    sensor1 = new Sensor;
    sensor1->setParentItem(this);
    sensor1->setMyMotor(this);
    sensor1->myMap = this->myMap;
    sensor1->setZValue(10);
    qDebug() << "--- 2 ---";
}


void Motorcycle::timerEvent(QTimerEvent *)
{
    qDebug() << "--- 3 ---";
    if(currentMilestone != NULL){
        qDebug() << "--- 5 ---";
        //sprawdza odległóść do obiektu
        QLineF lineToMilestone(scenePos(), currentMilestone->scenePos());
        qDebug() << "--- 6 ---";
        if (lineToMilestone.length() > aproxDistanceToMS)           //sprawdź czy punkt został osiagnięty
        {
            setPos(mapToParent(0, -step_length));                   //jeśli nie to zrób krok
            qDebug() << "--- 7 ---";
        }
        else                                                        //jeśli tak to pobierz nastpny punkt
        {
            qDebug() << "--- 8 ---";
            if(currentMilestone->isCrossroad == false){
                currentMilestone = currentMilestone->next;
                qDebug() << "--- 9 ---";
                faceToMilestone();
                qDebug() << "--- 10 ---";

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
    qDebug() << "--- a ---";
    int value = sensor1->checkSensor();
    if(value>=0){
        qDebug() << step << ": " << value;
    }
    step++;

    qDebug() << "--- 4 ---";
}

QRectF Motorcycle::boundingRect() const    //OBSZAR RYSOWANIA
{
    qreal adjust = 2;
    //return QRectF(-10 - adjust, -25 - adjust,20 + adjust, 45 + adjust);
    return QRectF(-60 - adjust, -120 - adjust,120 + adjust, 180 + adjust);

}


QPainterPath Motorcycle::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    //path.addRect(-10, -25, 20, 45);
    path.addRect(-10, 0, 20, 40);
    //path.addRect(-10, -35, 20, 10);
    return path;

}

void Motorcycle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QColor(100,100,100));
    painter->drawRoundedRect(-3, 0, 6, 12, 1, 1);
    painter->drawRoundedRect(-3, 30, 6, 12, 1, 1);

    //narysuj karoserię
    painter->setBrush(color);
    painter->drawRoundedRect(-5, 3, 10, 40, 5, 5);    //(-9, -20, 18, 40, 3, 3)

    //narysuj szubę
    painter->setBrush(QColor(220,220,255));
    painter->drawRect(-5, 9, 10, 5);

    painter->setBrush(QColor(30,30,30));
    painter->drawRoundedRect(-4, 20, 8, 15, 2, 2);

    //narysuj lampy
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-3, 0, 6, 4);


}

bool Motorcycle::faceToMilestone()     //skieruj samochód w kierunku następnego celu
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
