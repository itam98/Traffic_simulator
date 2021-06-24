#include "milestone.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>

Milestone::Milestone()
{

}

/**********************************************
 *  Obszar rysowania obiektu
 */
QRectF Milestone::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-5 - adjust, -5 - adjust,
                  10 + adjust, 10 + adjust);
}


/**********************************************
 *  Funkcja rysująca obiekt
 */
void Milestone::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::yellow);      //narysuj kropkę w celu debugowania
    painter->drawEllipse(-3, -3, 6, 6); //TODO:wyłączyć to w ostecznej wersji programu
}

/**********************************************
 *  Ustawia limit prędkości na danym odcinku drogi
 */
void Milestone::setSpeedLimit(qreal value)
{
    speedLimit = value;
}

/**********************************************
 *  Zwraca limit prędkości na danym odcinku drogi
 */
qreal Milestone::getSpeedLimit(){
    return speedLimit;
}

