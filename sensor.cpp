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
    //narysuj karoserię
    painter->setBrush(QColor(200,50,50,30));
    //painter->drawRoundedRect(-9, -20, 18, 40, 3, 3);
    //painter->drawLine(0,0,0,-50);

    static const QPointF points[4] = {
        QPointF(0.0, -20.0),
        QPointF(-20.0, -80.0),
        QPointF(20.0, -80.0)
    };

    painter->drawPolygon(points, 3);
            /*
    //narysuj szubę
    painter->setBrush(QColor(220,220,255));
    painter->drawRect(-8, -11, 16, 10);

    //narysuj lampy
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-9, -20, 8, 6);
    painter->drawEllipse(1, -20, 8, 6);
*/
}


