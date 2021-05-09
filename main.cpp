
#include "car.h"
#include "milestone.h"
#include "crossroad.h"
#include "road.h"
#include "router.h"

#include <QtMath>
#include <QtWidgets>
#include <QApplication>
#include <QDebug>
//#include <cmath>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 800);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);  //




    // tab parameters {x, y, angle, atrbA, atrB}
    /*int tabRoads[][]={
        {100,500,90,0,0},
        {100,100},
        {600,100},
        {1,1},
        {1,1},
        {1,1},
        {1,1}



    }*/



    int tabMilestones[][2]={
      {100,500}, //0
      {100,100}, //1
      {600,100}, //2
      {1,1},
      {1,1},
      {1,1},
      {1,1}
    };

    /*int tabCrossroads[][]={ //type(T or X),
        {, 500,500,0


    }*/

    int tabConnections[][2]={
        {0, 1},
        {1, 2},
        {2, 3}

    };
    /*Car *car = new Car;
    car->setPos(300,200);
    car->setSpeed(200);
    scene.addItem(car);*/

    Road tab[5];
    Router router;

    for(int i=0; i<5; i++){
        tab[i].setPos(200+100*i,200);
        scene.addItem(&tab[i]);
        if(i) router.connect(&tab[i-1], &tab[i]);
    }


    Road r2;
    r2.setPos(500,600);
    r2.setRotation(90);
    scene.addItem(&r2);



    router.connect(&tab[4], &r2);
    router.connect(&r2, &tab[0]);


   /* Milestone ms1;
    ms1.setPos(100,500);
    scene.addItem(&ms1);

    Milestone ms2;
    ms2.setPos(100,100);
    scene.addItem(&ms2);

    Milestone ms3;
    ms3.setPos(600,100);
    scene.addItem(&ms3);

    Crossroad cross1(&scene, 600, 600, &ms1, &ms1, &ms1, &ms1);

    ms1.nextMilestone = &ms2;
    ms2.nextMilestone = &ms3;
    ms3.nextMilestone = r1.mB;
    r2.mB->nextMilestone = &ms1;*/

    //r1.mB->nextMilestone = r2.mB;



    //ms3.nextMilestone = cross1.getEntrance_N();
    //cross1.entrance_W = &ms1;


    //qDebug() << ms1.nextMilestone->scenePos().x();



    //ms2.prevMilestone = &ms1;
    //ms3.prevMilestone = &ms2;




    Car car(tab[0].mB);
    car.setPos(100,500);
    car.setSpeed(400);
    scene.addItem(&car);

    /*Car car2(r2.mB);
    car2.setPos(100,550);
    car2.setSpeed(50);
    scene.addItem(&car2);

    Car car3(&r2.mB);
    car3.setPos(100,600);
    car3.setSpeed(50);
    scene.addItem(&car3);

    Car car4(&r2.mB);
    car4.setPos(150,650);
    car4.setSpeed(50);
    scene.addItem(&car4);

    Car car5(&r2.mB);
    car5.setPos(200,700);
    car5.setSpeed(50);
    scene.addItem(&car5);*/

    //car.setMilestone(&ms1);
    car.faceToMilestone();
    /*car2.faceToMilestone();
    car3.faceToMilestone();
    car4.faceToMilestone();
    car5.faceToMilestone();*/

    /*Milestone ms11;
    ms11.setPos(300,200);
    scene.addItem(&ms11);

    car.setMilestone(&ms11);
    car.faceToMilestone();

    Milestone *ms11 = new Milestone;
    ms11->setPos(300,200);
    scene.addItem(ms11);*/
/*
    Milestone *ms12 = new Milestone;
    ms12->setPos(300,600);
    scene.addItem(ms12);

    ms12->nextMilestone = &ms11;
    ms11.nextMilestone = ms12;

    car.setMilestone(ms12);
    car.faceToMilestone();*/

/*
    Car *car2 = new Car;
    car2->setPos(600,200);
    car2->setSpeed(200);
    scene.addItem(car2);

    Milestone *ms1 = new Milestone;
    ms1->setPos(600,200);
    scene.addItem(ms1);

    Milestone *ms2 = new Milestone;
    ms2->setPos(600,220);
    scene.addItem(ms2);

    Milestone *ms3 = new Milestone;
    ms3->setPos(600,240);
    scene.addItem(ms3);

    Milestone *ms4 = new Milestone;
    ms4->setPos(600,260);
    scene.addItem(ms4);

    Milestone *ms5 = new Milestone;
    ms5->setPos(600,280);
    scene.addItem(ms5);

    Milestone *ms6 = new Milestone;
    ms6->setPos(600,300);
    scene.addItem(ms6);

    Milestone *ms7 = new Milestone;
    ms7->setPos(600,320);
    scene.addItem(ms7);

    Milestone *ms8 = new Milestone;
    ms8->setPos(600,340);
    scene.addItem(ms8);

    Milestone *ms9 = new Milestone;
    ms9->setPos(600,600);
    scene.addItem(ms9);

    ms1->nextMilestone = ms2;
    ms2->nextMilestone = ms3;
    ms3->nextMilestone = ms4;
    ms4->nextMilestone = ms5;
    ms5->nextMilestone = ms6;
    ms6->nextMilestone = ms7;
    ms7->nextMilestone = ms8;
    ms8->nextMilestone = ms9;
    ms9->nextMilestone = ms1;

    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;
    ms1->prevMilestone = ms2;

    car2->setMilestone(ms2);
    car2->faceToMilestone();
*/

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    //view.setBackgroundBrush(QPixmap(":/images/background.jpg"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic Simulator"));
    //view.resize(900, 900);
    //view.show();
    //view.showMaximized();
    view.showMinimized();

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    //timer.start(1000 / 33);


    return app.exec();
}
//! [6]

