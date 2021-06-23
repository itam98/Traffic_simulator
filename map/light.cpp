#include "light.h"
#include <QPainter>
#include <QStyleOption>

Light::Light(QColor c)
{
    color = c;
}


QRectF Light::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}




void Light::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(color);
    painter->drawEllipse( -4,-4, 8, 8);

}
