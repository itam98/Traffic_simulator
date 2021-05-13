
#include "car.h"
#include "milestone.h"
#include "crossroad.h"
#include "road.h"
#include "router.h"

#include <QtMath>
#include <QtWidgets>
#include <QApplication>
#include <QDebug>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //QGraphicsScene scene;
    Router scene;
    scene.setSceneRect(0, 0, 800, 800);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);




    // tab parameters {x, y, angle} TODO: odczyt z pliku
    int tabRoads[14][3]={
        {300,80,0},     //0
        {400,100,45},
        {500,200,45},
        {500,300,90},
        {400,400,180},
        {300,420,150},
        {200,450,180},
        {100,400,-135},
        {80,300,-90},
        {100,200,-45},
        {200,100,-45},  //10
        //te po prawo na dole
        {700,400,45},
        {700,600,135},
        {500,600,-135}

    };




    /*int tabCrossroads[][]={ //type(T or X),
        {, 500,500,0


    }*/

    int tabConn[][2]={
        {0, 1},
        {1, 2},
        {2, 3},
        //{3, 4},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 8},
        {8, 9},
        {9, 10},
        {10, 0},
        {11, 12},
        {12,13},
    };



    Road tab[15];
    //Router router;


    for(int i=0; i<14; i++){
        tab[i].setPos(tabRoads[i][0],tabRoads[i][1]);
        tab[i].setRotation(tabRoads[i][2]);
        scene.addItem(&tab[i]);

    }

    int t_size = sizeof tabConn / sizeof tabConn[0];

    for(int i=0; i<t_size; i++){
        scene.connect(&scene, &tab[tabConn[i][0]], &tab[tabConn[i][1]]);
    }

    Crossroad cross1;
    cross1.setPos(500,400);
    scene.addItem(&cross1);

    scene.connect(&scene, &tab[3], cross1.road[Entrance::North], false, true);
    scene.connect(&scene, cross1.road[Entrance::West], &tab[4]);

    scene.connect(&scene, cross1.road[Entrance::East], &tab[11]);
    scene.connect(&scene, &tab[13], cross1.road[Entrance::South], false, true);

     //router.connect(&tab[11], &tab[0]);





    Car car(tab[0].mP);
    car.setPos(tab[0].pos());
    car.setSpeed(100);
    scene.addItem(&car);

    Car car2(tab[8].mP);
    car2.setPos(tab[8].pos());
    car2.setSpeed(100);
    scene.addItem(&car2);

    /*Car car3(tab[8].mP);
    car3.setPos(tab[8].pos());
    car3.setSpeed(100);
    scene.addItem(&car3);

    Car car4(tab[8].mL);
    car4.setPos(tab[8].pos());
    car4.setSpeed(110);
    scene.addItem(&car4);

    Car car5(tab[8].mL);
    car5.setPos(tab[8].pos());
    car5.setSpeed(90);
    scene.addItem(&car5);*/


    car.faceToMilestone();
    car2.faceToMilestone();
    /*car3.faceToMilestone();
    car4.faceToMilestone();
    car5.faceToMilestone();*/




    QGraphicsView view(&scene);
    //view.scale(0.5 , 0.5);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap("bg.jpg"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic Simulator"));
    view.resize(900, 900);
    view.show();
    //view.showmLximized();
    //view.showMinimized();

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    //timer.start(1000 / 33);


    return app.exec();
}


