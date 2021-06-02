#include "background.h"

#include <QPainter>
#include <QStyleOption>

Background::Background()
{

}

QRectF Background::boundingRect() const
{
    return QRectF(0, 0,800, 800);
}


void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{





}



