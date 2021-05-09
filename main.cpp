
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
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);



    // tab parameters {x, y, angle} TODO: odczyt z pliku
    int tabRoads[12][3]={
        {300,100,0},
        {400,100,45},
        {500,200,45},
        {500,300,90},
        {500,400,135},
        {400,600,135},
        {300,600,180},
        {200,500,-135},
        {100,400,-135},
        {100,300,-90},
        {100,200,-45},
        {200,100,-45}

    };




    /*int tabCrossroads[][]={ //type(T or X),
        {, 500,500,0


    }*/

    int tabConnections[][2]={
        {0, 1},
        {1, 2},
        {2, 3}

    };



    Road tab[12];
    Router router;

    /*for(int i=0; i<5; i++){
        tab[i].setPos(200+100*i,200);
        scene.addItem(&tab[i]);
        if(i) router.connect(&tab[i-1], &tab[i]);
    }*/

    for(int i=0; i<12; i++){
        tab[i].setPos(tabRoads[i][0],tabRoads[i][1]);
        tab[i].setRotation(tabRoads[i][2]);
        scene.addItem(&tab[i]);
        if(i) router.connect(&tab[i-1], &tab[i]);
    }
     router.connect(&tab[11], &tab[0]);


    Crossroad cross1;
    cross1.setPos(300,300);
    scene.addItem(&cross1);


    Car car(tab[0].mB);
    car.setPos(100,500);
    car.setSpeed(300);
    scene.addItem(&car);

    Car car2(tab[8].mB);
    car2.setPos(100,550);
    car2.setSpeed(250);
    scene.addItem(&car2);

    Car car3(tab[8].mB);
    car3.setPos(100,600);
    car3.setSpeed(200);
    scene.addItem(&car3);

    Car car4(tab[8].mA);
    car4.setPos(150,650);
    car4.setSpeed(150);
    scene.addItem(&car4);

    Car car5(tab[8].mA);
    car5.setPos(200,700);
    car5.setSpeed(400);
    scene.addItem(&car5);


    car.faceToMilestone();
    car2.faceToMilestone();
    car3.faceToMilestone();
    car4.faceToMilestone();
    car5.faceToMilestone();




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


