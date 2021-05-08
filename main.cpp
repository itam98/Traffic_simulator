#include "graphicsview.h"
#include "car.h"
#include "milestone.h"
#include "crossroad.h"

#include <QApplication>
#include <cmath>

//static constexpr int MouseCount = 7;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 800);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);  //


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



    Milestone ms1;
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
    ms3.nextMilestone = cross1.getEntrance_N();
    //cross1.entrance_W = &ms1;

    ms2.prevMilestone = &ms1;
    ms3.prevMilestone = &ms2;



    Car car(&ms1);
    car.setPos(100,500);
    car.setSpeed(800);
    scene.addItem(&car);

    Car car2(&ms1);
    car2.setPos(100,550);
    car2.setSpeed(750);
    scene.addItem(&car2);

    Car car3(&ms1);
    car3.setPos(100,600);
    car3.setSpeed(700);
    scene.addItem(&car3);

    Car car4(&ms1);
    car4.setPos(150,650);
    car4.setSpeed(650);
    scene.addItem(&car4);

    Car car5(&ms1);
    car5.setPos(200,700);
    car5.setSpeed(500);
    scene.addItem(&car5);

    //car.setMilestone(&ms1);
    car.faceToMilestone();
    car2.faceToMilestone();
    car3.faceToMilestone();
    car4.faceToMilestone();
    car5.faceToMilestone();

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

    GraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic"));
    view.showMaximized();
    //view.showMinimized();


    return app.exec();
}
//! [6]

