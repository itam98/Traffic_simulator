#include "router.h"


Router::Router()
{

}





void Router::connect(QGraphicsScene *scene, Road *road1, Road *road2, bool inv1, bool inv2)
{
    if(inv1==false && inv2==false){
        road1->mP->next = road2->mP;
        road2->mP->prev = road1->mP;

        road2->mL->next = road1->mL;
        road1->mL->prev = road2->mL;
    }

    if(inv1==false && inv2==true){
        road1->mP->next = road2->mL;
        road2->mL->prev = road1->mP;

        road2->mP->next = road1->mL;
        road1->mL->prev = road2->mP;
    }
    //TODO: dodać pozostałe przypadki


    QPointF a = road1->scenePos();
    QPointF b = road2->scenePos();


    QPen pen(Qt::white, 3, Qt::DashLine, Qt::FlatCap, Qt::RoundJoin);
    QPen pen2(Qt::black, 70, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    pen.setDashOffset(10);


    //painter.drawArc(rectangle, startAngle, spanAngle);

    scene->addLine(a.x(), a.y(),b.x(),b.y(),pen2);
    scene->addLine(a.x(), a.y(),b.x(),b.y(),pen);



}

