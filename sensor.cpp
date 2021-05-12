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
    path.addRect(-20, -50, 40, 50);
    return path;

}

void Sensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(QColor(200,50,50,30));
    painter->setPen(Qt::NoPen);

    static const QPointF points[4] = {
        QPointF(0.0, -20.0),
        QPointF(-20.0, -80.0),
        QPointF(20.0, -80.0)
    };

    painter->drawPolygon(points, 3);

}


