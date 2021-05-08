#include "car.h"

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
    nextMilestone=nextMS;
    faceToMilestone();
}



void Car::timerEvent(QTimerEvent *)
{

    QLineF lineToMilestone(QPointF(0, 0), mapFromScene(nextMilestone->x(), nextMilestone->y()));    //sprawdza odległóść do obiektu
    if (lineToMilestone.length() > aproxDistanceToMS)           //sprawdź czy punkt został osiagnięty
    {
        setPos(mapToParent(0, -step_length));                   //jeśli nie to zrób krok
    }
    else                                                        //jeśli tak to pobierz nastpny punkt
    {
        nextMilestone = nextMilestone->nextMilestone;
        faceToMilestone();
    }

}

QRectF Car::boundingRect() const    //metoda dziedziczona po wirtualnej metodzie w graphicsobject a dokładniej grpahicsItem
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -25 - adjust,
                  20 + adjust, 45 + adjust);
}


QPainterPath Car::shape() const     //kształt wykorzystywany w detekcji kolizji
{
    QPainterPath path;
    path.addRect(-10, -25, 20, 45);
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

void Car::faceToMilestone()     //skieruj samochód w kierunku następnego celu
{
    std::complex<double> temp(  nextMilestone->x()-x()  ,  -(nextMilestone->y()-y())  ); //tworzy liczbę zepoloną
    qreal angle = qRadiansToDegrees(  std::arg(temp)  );    //zwraca kat powyższej liczby
    //qInfo() << "Milestone x: " << nextMilestone->x() << " y: " << nextMilestone->y() << "Car x: "<< x() << " y: " << y() << "angle: "<< angle;
    setTransform(QTransform().rotate(90-angle), false);
}

void Car::setMilestone(Milestone *nextMS)
{
    nextMilestone = nextMS;
}

void Car::setSpeed(qreal value)
{
    speed = value;      //ustaw ograniczenie prędkości
    step_length = value/framerate;       //oblicz jaki to da krok na jeden krok symulacji
    aproxDistanceToMS = qCeil(step_length/1.9); //wyzancz margines błędu osiągnicia celu z dokładnością do +- pół kroku
}





