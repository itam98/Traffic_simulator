
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


int main(int argc, char **argv)
{
    QApplication app(argc, argv);


    Map scene;
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

    car.faceToMilestone();
    car2.faceToMilestone();
    car3.faceToMilestone();
    car4.faceToMilestone();
    motor.faceToMilestone();

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");  //hide scrollbar
    view.verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic Simulator"));
    view.resize(1700, 1000);
    view.show();


    return app.exec();
}


