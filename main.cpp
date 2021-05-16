
#include "car.h"
#include "milestone.h"
#include "crossroad.h"
#include "road.h"
#include "map.h"

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


    struct element {


        int x,y;
        int rotation;
        int type = 1; //1-raod, 2-crossroad

        element(int ix, int iy,int irot, int itype) :
            x(ix), y(iy),rotation(irot),type(itype){}

    };

    struct connection {

        int element1_id;
        bool element1_inv;
        int element1_type; //0-milestone 1-raod, 2-crossroad
        Entrance entrance1;

        int element2_id;
        bool element2_inv;
        bool element2_type;
        Entrance entrance2;

        connection(int id1, int inv1,int type1, int id2, int inv2,int type2) : element1_id(id1), element1_inv(inv1),
            element1_type(type1),element2_id(id2), element2_inv(inv2),element2_type(type2) {}


    };


    QList<element> listOfElements;
    QList<Road> listOfRoads;
    QList<Crossroad> listOfCrossroads;

    listOfElements.append(element(300,80,0,1));     //0
    listOfElements.append(element(400,100,45,1));
    listOfElements.append(element(500,200,45,1));
    listOfElements.append(element(500,300,90,1));
    listOfElements.append(element(400,400,180,1));
    listOfElements.append(element(300,420,150,1));
    listOfElements.append(element(200,450,180,1));
    listOfElements.append(element(100,400,-135,1));
    listOfElements.append(element(80,300,-90,1));
    listOfElements.append(element(100,200,-45,1));
    listOfElements.append(element(200,100,-45,1));  //10

    listOfElements.append(element(700,400,45,1));   //11
    listOfElements.append(element(700,600,135,1));
    listOfElements.append(element(500,600,-135,1));

    // tab parameters {x, y, angle} TODO: odczyt z pliku
    /*int tabRoads[14][3]={
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

    };*/




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
            tab[i].setPos(listOfElements[i].x,listOfElements[i].y);
            tab[i].setRotation(listOfElements[i].rotation);
            scene.addItem(&tab[i]);

        }

    /*for(int i=0; i<14; i++){
        tab[i].setPos(tabRoads[i][0],tabRoads[i][1]);
        tab[i].setRotation(tabRoads[i][2]);
        scene.addItem(&tab[i]);

    }*/

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


