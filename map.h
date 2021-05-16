#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QtWidgets>
#include <QApplication>

#include "milestone.h"
#include "crossroad.h"
#include "road.h"

enum Element_type {tMilestone=0, tRoad=1, tCrossroad=2};

struct element {
    int x,y;
    int rotation;
    Element_type type; //1-raod, 2-crossroad
    element(int ix, int iy,int irot, Element_type itype) :
        x(ix), y(iy),rotation(irot),type(itype){}
};



class Map : public QGraphicsScene
{
    Q_OBJECT

public:
    Map();

    QList<element> listOfElements;
    QList<Road> listOfRoads;
    QList<Crossroad> listOfCrossroads;

    void connect(QGraphicsScene *scene, Road *road1, Road *road2, bool inv1=false, bool inv2=false);

};

#endif // MAP_H
