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

QRectF Road::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -70 - adjust,
                  20 + adjust, 120 + adjust);
}


/*QPainterPath Road::shape() const
{
    QPainterPath path;
    path.addRect(-2, -30, 11, 60);
    return path;
}*/

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(Qt::black);
    //painter->drawRect(-2, -25, 4, 50);
    painter->drawLine(0, -w/2, 0, w/2);
    painter->drawLine(-2, -w/2, 2, -w/2);
    painter->drawLine(-2, w/2, 2, w/2);

    painter->setBrush(Qt::green);
    //painter->drawEllipse(-2, -2, 4, 4);

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
        /*// value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }*/

        qDebug()<<"hop";
        Map *temp;
        temp = (Map*)scene();
        temp->plot();
    }
    qDebug() << "new location"<< pos().x()<<" "<<pos().y();
    return QGraphicsItem::itemChange(change, value);
}

