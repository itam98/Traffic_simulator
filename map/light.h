#ifndef LIGHT_H
#define LIGHT_H

#include <QGraphicsObject>


class Light : public QGraphicsObject
{

    Q_OBJECT

public:
    Light(QColor c);

    QColor color;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    virtual ~Light() {};

};

#endif // LIGHT_H
