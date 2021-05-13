#include "car.h"
#include "crossroad.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>

Car::Car(Milestone *nextMS) : color(QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256))
{
    startTimer(1000/framerate);
    currentMilestone=nextMS;
    faceToMilestone();
    defaultSpeed = 50+ QRandomGenerator::global()->bounded(100);

    sensor1 = new Sensor;
    sensor1->setParentItem(this);
}



void Car::timerEvent(QTimerEvent *)
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
                currentMilestone = cross->getNextMilestone(currentMilestone, (Direction)random);
                faceToMilestone();


            }
        }

    }


    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this,Qt::IntersectsItemShape);

    setSpeed(defaultSpeed);
    foreach (QGraphicsItem * item, collidingItems){
        Car * carItem = dynamic_cast<Car*>(item);
        if(carItem){
            setSpeed(carItem->getSpeed());
        }


    }


/*    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                           << mLpToScene(0, 0)
                           << mLpToScene(-30, -50)
                           << mLpToScene(30, -50));
    setSpeed(150);

    for (const QGraphicsItem *item : dangerMice)
    {
        if (item == this)
            continue;
        if( item->metaObject()->className() )setSpeed(30);
    }
*/
    /*if(!scene()->collidingItems(this).isEmpty() ){
        for (int i = 0; i < scene()->collidingItems(this).size(); ++i) {
            if (scene()->collidingItems(this).at(i))
                cout << "Found Jane at position " << i << Qt::endl;
        }

        //qDebug() << "collison";
        setSpeed(100);
    }
    else setSpeed(30);
*/
       // qobject_cast<Car*>(instance);

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
    path.addRect(-10, -35, 20, 100);
    //path.addRect(-10, -35, 20, 10);
    return path;

}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //narysuj karoserię
    painter->setBrush(color);
    painter->drawRoundedRect(-9, -20, 18, 40, 3, 3);

    //narysuj szubę
    painter->setBrush(QColor(220,220,255));
    painter->drawRect(-8, -11, 16, 10);

    //narysuj lampy
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-9, -20, 8, 6);
    painter->drawEllipse(1, -20, 8, 6);

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

void Car::setMilestone(Milestone *nextMS)
{
    currentMilestone = nextMS;
}

void Car::setSpeed(qreal value)
{
    speed = value;      //ustaw ograniczenie prędkości
    step_length = value/framerate;       //oblicz jaki to da krok na jeden krok symulacji
    aproxDistanceToMS = qCeil(step_length/1.9); //wyzancz mLrgines błędu osiągnicia celu z dokładnością do +- pół kroku
}


qreal Car::getSpeed(){
    return speed;
}


