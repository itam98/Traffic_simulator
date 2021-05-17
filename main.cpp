
#include "car/car.h"

#include "map/milestone.h"
#include "map/crossroad.h"
#include "map/road.h"
#include "map/map.h"

#include <QtMath>
#include <QtWidgets>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);



    //QGraphicsScene scene;
    Map scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.loadFromFile("../Traffic_simulator/saves/default.txt");
    scene.init();


    Car car(scene.listOfRoads[0]->mP);
    car.setPos(scene.listOfRoads[0]->pos());
    car.setSpeed(100);
    scene.addItem(&car);

    Car car2(scene.listOfRoads[8]->mP);
    car2.setPos(scene.listOfRoads[8]->pos());
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



    QMenuBar *menu = new QMenuBar;
    QMenu *file = new QMenu();
    file->addMenu("&File");
    menu->addMenu(file);


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

    MainWindow mainWin;
    mainWin.setCentralWidget(&view);
    //view.show();
    //view.showMaximized();
    //view.showMinimized();

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    //timer.start(1000 / 33);
    mainWin.show();

    return app.exec();
}


