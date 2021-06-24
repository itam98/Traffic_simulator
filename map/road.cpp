#include "road.h"
#include "map.h"

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPainter>
#include <QStyleOption>
#include <qmath.h>



int Road::objCnt;

Road::Road(bool isCrossroad){
    //L A   TODO: zmienić A i B na L i P
    //x>
    //P B
    setVisible(false);
    if( !isCrossroad ) objNo = ++objCnt-1;
    else objNo = -1;


    mL = new Milestone;
    mP = new Milestone;

    mL->setParentItem(this);
    mL->setPos(0,-w/4);

    mP->setParentItem(this);
    mP->setPos(0,w/4);

    mL->itemsRoad = this;
    mP->itemsRoad = this;
    if(!isCrossroad)this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

Road::~Road()
{
    if( !isCrossroad )--objCnt;
}

/**********************************************
 *  Obszar rysowania obiektu
 */
QRectF Road::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -70 - adjust,
                  20 + adjust, 120 + adjust);
}



/**********************************************
 *  Funkcja rysująca obiekt
 */
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(Qt::black);
    //painter->drawRect(-2, -25, 4, 50);
    painter->drawLine(0, -w/2, 0, w/2);
    painter->drawLine(-2, -w/2, 2, -w/2);
    painter->drawLine(-2, w/2, 2, w/2);

    painter->setBrush(Qt::black);
    painter->drawLine(0, -4, 9, 0);
    painter->drawLine(0, 4, 9, 0);
    if( objNo != -1 ){
        QString s = QString::number(objNo);
        painter->drawText(0,-50, s);
    }
}


QVariant Road::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        Map *temp;
        temp = (Map*)scene();
        temp->plot();
    }

    return QGraphicsItem::itemChange(change, value);
}

