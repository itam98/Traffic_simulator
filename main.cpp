
#include "car/car.h"
#include "car/motorcycle.h"

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
    qDebug()<<"adres scny:"<<&scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.loadFromFile("../Traffic_simulator/saves/default2.txt");
    scene.init();



    Car car(scene.listOfRoads[0]->mP, &scene);
    car.setPos(scene.listOfRoads[0]->pos());
    scene.addItem(&car);
    car.setZValue(10);
    scene.listOfCars.append(&car);

    Car car2(scene.listOfRoads[8]->mP, &scene);
    car2.setPos(scene.listOfRoads[8]->pos());
    scene.addItem(&car2);
    car2.setZValue(10);
    scene.listOfCars.append(&car2);


    Car car3(scene.listOfRoads[15]->mL, &scene);
    car3.setPos(scene.listOfRoads[15]->pos());
    scene.addItem(&car3);
    car3.setZValue(10);
    scene.listOfCars.append(&car3);

    Car car4(scene.listOfRoads[13]->mP, &scene);
    car4.setPos(scene.listOfRoads[13]->pos());
    scene.addItem(&car4);
    car4.setZValue(10);
    scene.listOfCars.append(&car4);


    Motorcycle motor(scene.listOfRoads[16]->mL, &scene);
    motor.setPos(scene.listOfRoads[16]->pos());
    scene.addItem(&motor);
    motor.setZValue(10);
    motor.faceToMilestone();




    car.faceToMilestone();
    car2.faceToMilestone();
    car3.faceToMilestone();
    car4.faceToMilestone();




    //QMenuBar *menu = new QMenuBar;
    //QMenu *file = new QMenu();
    //file->addMenu("&File");
    //menu->addMenu(file);


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
    view.resize(2500, 1500);

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


