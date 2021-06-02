#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QtWidgets>
#include <QApplication>


#include "map/milestone.h"
#include "map/crossroad.h"
#include "map/road.h"

enum Element_type {tMilestone=0, tRoad=1, tCrossroad=2};

struct coord {
    int x,y;
    int rotation;
    coord(int ix, int iy,int irot) :
        x(ix), y(iy),rotation(irot){}
};

struct connection{
    Element_type type1, type2;  //typ skrzyżowanie, droga, punkt
    int id1, id2;
    Entrance entrance1, entrance2;  //dotyczy tylko skrzyżowań
    bool inv1, inv2;
    connection(Element_type t1, Element_type t2,int id1, int id2, Entrance ent1, Entrance ent2, bool inv1, bool inv2) :
        type1(t1), type2(t2),id1(id1),id2(id2),entrance1(ent1),entrance2(ent2),inv1(inv1),inv2(inv2){}
};

class Map : public QGraphicsScene
{
    Q_OBJECT

public:
    Map();


    QList<Road *> listOfRoads;
    QList<Crossroad *> listOfCrossroads;

    void connect(QGraphicsScene *scene, Road *road1, Road *road2, bool inv1=false, bool inv2=false);

    void plot();

    void loadFromFile(QString name);

    int numberOfConnections;


    void init();







private:

    int loadedSceneRect[4];

    QList<coord> loadedRoads;
    QList<coord> loadedCrossroads;
    QList<connection> loadedConnections;

    QList<coord> toSaveRoads;
    QList<coord> toSaveCrossroads;
    QList<connection> toSaveConnections;

};

#endif // MAP_H
