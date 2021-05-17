#include "map.h"

Map::Map()
{

}


void Map::connect(QGraphicsScene *scene, Road *road1, Road *road2, bool inv1, bool inv2)
{
    if(inv1==false && inv2==false){
        road1->mP->next = road2->mP;
        road2->mP->prev = road1->mP;

        road2->mL->next = road1->mL;
        road1->mL->prev = road2->mL;
    }

    if(inv1==false && inv2==true){
        road1->mP->next = road2->mL;
        road2->mL->prev = road1->mP;

        road2->mP->next = road1->mL;
        road1->mL->prev = road2->mP;
    }
    //TODO: dodać pozostałe przypadki


    QPointF a = road1->scenePos();
    QPointF b = road2->scenePos();


    QPen pen(Qt::white, 3, Qt::DashLine, Qt::FlatCap, Qt::RoundJoin);
    QPen pen2(Qt::black, 70, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    pen.setDashOffset(10);


    scene->addLine(a.x(), a.y(),b.x(),b.y(),pen2);
    scene->addLine(a.x(), a.y(),b.x(),b.y(),pen);


    return;
}



void Map::loadFromFile(QString name){

    QFile file(name);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "error opening file: " << file.errorString();
        QMessageBox::warning(0, "Błąd odczytu",file.errorString());
        return;
    }

    QString line;
    QTextStream stream(&file);

    int line_index=0;   //index of line
    //int roads_index, crossroads_index, connections_index;
    int roads_cnt=0, crossroads_cnt=0, connections_cnt=0;
    bool flag_r=false, flag_c=false, flag_conn=false;

    while (!stream.atEnd()){
        line = stream.readLine();

        if( line.indexOf("$SIZE") != -1){       //reading scene parameters
            int a=line.indexOf("(");
            int b=line.indexOf(")");
            QString subString = line.mid(a+1, b-a-1);

            QStringList list = subString.split(QLatin1Char(','));

            for(int i=0; i <4 ; i++){
                loadedSceneRect[i]=list[i].toInt();
            }
        }

        //------------ Load roads ------------
        if(flag_r){
            if(line.indexOf("#") != -1){
                roads_cnt++;

                int a=line.indexOf("(");
                int b=line.indexOf(")");
                QString subString = line.mid(a+1, b-a-1);
                QStringList list = subString.split(QLatin1Char(','));

                int x = list[0].toInt();
                int y = list[1].toInt();
                int rot = list[2].toInt();

                loadedRoads.append(coord(x,y,rot));
            }
            else flag_r=false;
        }


        if( line.indexOf("$ROADS;") != -1){   //set flag if found ROADS data block
            //roads_index = line_index;
            flag_r=true;
        }
        //----------------------------------


        //------------ Load crossroades ------------
        if(flag_c){
            if(line.indexOf("#") != -1){
                crossroads_cnt++;

                int a=line.indexOf("(");
                int b=line.indexOf(")");
                QString subString = line.mid(a+1, b-a-1);
                QStringList list = subString.split(QLatin1Char(','));

                int x = list[0].toInt();
                int y = list[1].toInt();
                int rot = list[2].toInt();

                loadedCrossroads.append(coord(x,y,rot));
            }
            else flag_c=false;
        }


        if( line.indexOf("$CROSSROADS;") != -1){   //set flag if found CROSSROADS data block
            //crossroads_index = line_index;
            flag_c=true;
        }
        //----------------------------------





        //------------ Load connections ------------
        if(flag_conn){
            if(line.indexOf("#") != -1){
                connections_cnt++;

                int a=line.indexOf("(");
                int b=line.indexOf(")");
                QString subString = line.mid(a+1, b-a-1);
                QStringList list = subString.split(QLatin1Char(','));

                Element_type type1 = Element_type::tRoad , type2 = Element_type::tRoad; //inicjalizacja
                Entrance entrance1 = Entrance::None , entrance2 = Entrance::None;

                if(list[0] == "ROAD") type1 =  Element_type::tRoad;
                else if(list[0] == "CROSSROAD") type1 = Element_type::tCrossroad;

                if(list[1] == "ROAD") type2 = Element_type::tRoad;
                else if(list[1] == "CROSSROAD") type2 = Element_type::tCrossroad;

                int id1 = list[2].toInt();
                int id2 = list[3].toInt();

                if(list[4] == "NORTH") entrance1 = Entrance::North;
                else if(list[4] == "EAST") entrance1 = Entrance::East;
                else if(list[4] == "SOUTH") entrance1 = Entrance::South;
                else if(list[4] == "WEST") entrance1 = Entrance::West;

                if(list[5] == "NORTH") entrance2 = Entrance::North;
                else if(list[5] == "EAST") entrance2 = Entrance::East;
                else if(list[5] == "SOUTH") entrance2 = Entrance::South;
                else if(list[5] == "WEST") entrance2 = Entrance::West;


                int inv1 = list[6].toInt();
                int inv2 = list[7].toInt();

                loadedConnections.append(connection(type1,type2,id1,id2,entrance1,entrance2,inv1,inv2));
            }
            else flag_conn=false;
        }


        if( line.indexOf("$CONNECTIONS;") != -1){   //set flag if found CONNECTIONS data block
            //connections_index = line_index;
            flag_conn=true;
        }
        //----------------------------------





        line_index++;
    }
        //qDebug()<<"roads_index:"<<roads_index<<"crossroads_index:"<<crossroads_index<<"connections_index:"<<connections_index;
        //qDebug()<<"roads_cnt:"<<roads_cnt<<"crossroads_cnt:"<<crossroads_cnt<<"connections_cnt:"<<connections_cnt;




/*
    qDebug()<<"ROADS";
    for(int i=0; i<roads_cnt;i++){
        qDebug()<< "("<< loadedRoads[i].x<< ","<< loadedRoads[i].y<< ","<< loadedRoads[i].rotation<<")";

    }

    qDebug()<<"CROSSROADS";
        for(int i=0; i<crossroads_cnt;i++){
            qDebug()<< "("<< loadedCrossroads[i].x<< ","<< loadedCrossroads[i].y<< ","<< loadedCrossroads[i].rotation<<")";

        }

    qDebug()<<"CONNECTIONS";
        for(int i=0; i<connections_cnt;i++){
        qDebug()<< "("<< loadedConnections[i].type1<< ","<< loadedConnections[i].type2<< ","<< loadedConnections[i].id1<< ","<< loadedConnections[i].id2<< ","<< loadedConnections[i].entrance1<< ","<< loadedConnections[i].entrance2<< ","<< loadedConnections[i].inv1<< ","<< loadedConnections[i].inv2<<")";

   }*/

    file.close();

    numberOfConnections = connections_cnt;

    return;
}




void Map::init(){

    setSceneRect(loadedSceneRect[0], loadedSceneRect[1], loadedSceneRect[2], loadedSceneRect[3]);

    for(int i=0; i<loadedRoads.length(); i++){      //creating road objects basing on loadedRoads
        Road* temp = new Road;
        temp->setPos(loadedRoads[i].x,loadedRoads[i].y);
        temp->setRotation(loadedRoads[i].rotation);
        addItem(temp);
        listOfRoads.append(temp);
    }


    for(int i=0; i<loadedCrossroads.length(); i++){
        Crossroad* temp = new Crossroad;
        temp->setPos(loadedCrossroads[i].x,loadedCrossroads[i].y);
        temp->setRotation(loadedCrossroads[i].rotation);
        addItem(temp);
        listOfCrossroads.append(temp);
    }


    for(int i=0; i<numberOfConnections; i++){
        if(loadedConnections[i].type1 == Element_type::tRoad && loadedConnections[i].type2 == Element_type::tRoad){
            Road *road1 = listOfRoads[loadedConnections[i].id1];
            Road *road2 = listOfRoads[loadedConnections[i].id2];
            connect(this, road1 ,road2 , loadedConnections[i].inv1, loadedConnections[i].inv2);

        }
        else if(loadedConnections[i].type1 == Element_type::tRoad && loadedConnections[i].type2 == Element_type::tCrossroad){
            Road *road1 = listOfRoads[loadedConnections[i].id1];

            int _id2 = loadedConnections[i].id2;
            Entrance n = loadedConnections[i].entrance2;
            Road *road2 = listOfCrossroads[_id2]->road[n];

            connect(this, road1, road2, loadedConnections[i].inv1, loadedConnections[i].inv2);
        }
        else if(loadedConnections[i].type1 == Element_type::tCrossroad && loadedConnections[i].type2 == Element_type::tRoad){
            int _id1 = loadedConnections[i].id1;
            Entrance n = loadedConnections[i].entrance1;
            Road *road1 = listOfCrossroads[_id1]->road[n];

            Road *road2 = listOfRoads[loadedConnections[i].id2];
            connect(this, road1,road2 , loadedConnections[i].inv1, loadedConnections[i].inv2);
        }
        else if(loadedConnections[i].type1 == Element_type::tCrossroad && loadedConnections[i].type2 == Element_type::tCrossroad){
            int _id1 = loadedConnections[i].id1;
            int _id2 = loadedConnections[i].id2;

            Entrance n = loadedConnections[i].entrance1;
            Road *road1 = listOfCrossroads[_id1]->road[n];

            n = loadedConnections[i].entrance2;
            Road *road2 = listOfCrossroads[_id2]->road[n];

            connect(this, road1, road2, loadedConnections[i].inv1, loadedConnections[i].inv2);
        }
    }


}



