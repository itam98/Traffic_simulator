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
    startTimer(1000/framerate);
    currentMilestone=nextMS;
    faceToMilestone();
    defaultSpeed = 70+ QRandomGenerator::global()->bounded(10);
    setSpeed(defaultSpeed);

    sensor1 = new Sensor;
    sensor1->setParentItem(this);
    sensor1->setMyMotor(this);
    sensor1->myMap = this->myMap;
    sensor1->setZValue(10);

}


void Motorcycle::timerEvent(QTimerEvent *)
{

    if(currentMilestone != NULL){

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

QRectF Motorcycle::boundingRect() const    //OBSZAR RYSOWANIA
{

    return QRectF(-62, -122 ,122, 182 );

}


QPainterPath Motorcycle::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    path.addRect(-8, 0, 16, 30);
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
