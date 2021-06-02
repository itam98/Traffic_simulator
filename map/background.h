#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsObject>

#include <QDebug>


class Background : public QGraphicsObject
{

    Q_OBJECT
public:
    Background();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;


};

#endif // BACKGROUND_H
