
#include "car/car.h"

#include "map/milestone.h"
#include "map/crossroad.h"
#include "map/road.h"
#include "map/map.h"

#include <QtMath>
#include <QtWidgets>
#include <QApplication>
#include <QDebug>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //QGraphicsScene scene;
    Map scene;
    scene.setSceneRect(0, 0, 800, 800);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.loadFromFile("../Traffic_simulator/saves/default.txt");




    Road tab[15];


    for(int i=0; i<14; i++){
            tab[i].setPos(scene.loadedRoads[i].x,scene.loadedRoads[i].y);
            tab[i].setRotation(scene.loadedRoads[i].rotation);
            scene.addItem(&tab[i]);
    }


    Crossroad tabCross[1];
    tabCross[0].setPos(500,400);
    scene.addItem(&tabCross[0]);


    for(int i=0; i<scene.numberOfConnections; i++){
        if(scene.loadedConnections[i].type1 == Element_type::tRoad && scene.loadedConnections[i].type2 == Element_type::tRoad){
            Road *road1 = &tab[scene.loadedConnections[i].id1];
            Road *road2 = &tab[scene.loadedConnections[i].id2];
            scene.connect(&scene, road1 ,road2 , scene.loadedConnections[i].inv1, scene.loadedConnections[i].inv2);

        }
        else if(scene.loadedConnections[i].type1 == Element_type::tRoad && scene.loadedConnections[i].type2 == Element_type::tCrossroad){
            Road *road1 = &tab[scene.loadedConnections[i].id1];

            int _id2 = scene.loadedConnections[i].id2;
            Entrance n = scene.loadedConnections[i].entrance2;
            Road *road2 = tabCross[_id2].road[n];

            scene.connect(&scene, road1, road2, scene.loadedConnections[i].inv1, scene.loadedConnections[i].inv2);
        }
        else if(scene.loadedConnections[i].type1 == Element_type::tCrossroad && scene.loadedConnections[i].type2 == Element_type::tRoad){
            int _id1 = scene.loadedConnections[i].id1;
            Entrance n = scene.loadedConnections[i].entrance1;
            Road *road1 = tabCross[_id1].road[n];

            Road *road2 = &tab[scene.loadedConnections[i].id2];
            scene.connect(&scene, road1,road2 , scene.loadedConnections[i].inv1, scene.loadedConnections[i].inv2);
        }
        else if(scene.loadedConnections[i].type1 == Element_type::tCrossroad && scene.loadedConnections[i].type2 == Element_type::tCrossroad){
            int _id1 = scene.loadedConnections[i].id1;
            int _id2 = scene.loadedConnections[i].id2;

            Entrance n = scene.loadedConnections[i].entrance1;
            Road *road1 = tabCross[_id1].road[n];

            n = scene.loadedConnections[i].entrance2;
            Road *road2 = tabCross[_id2].road[n];

            scene.connect(&scene, road1, road2, scene.loadedConnections[i].inv1, scene.loadedConnections[i].inv2);
        }
    }


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
    //view.setBackgroundBrush(QPixmap("bg.jpg"));


    view.horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");  //hide scrollbar
    view.verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic Simulator"));
    view.resize(900, 900);
    view.show();
    //view.showMaximized();
    //view.showMinimized();

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    //timer.start(1000 / 33);


    return app.exec();
}


