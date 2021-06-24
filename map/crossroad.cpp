#include "crossroad.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <complex>
#include <QDebug>




Crossroad::Crossroad()
{

    //   N
    // W + E
    //   S

    state=0;
    timer=15;
    startTimer(1000);

    int coord[4][3]={           //x,y, rotation
        {0, -width/2 , -90},
        {width/2, 0  , 0},
        {0, width/2  , 90},
        {-width/2, 0 , 180}
    };

    int red_coord[4][2]={           //x,y, rotation
        {-width/2, -width/2-10},
        {width/2+10, -width/2},
        {width/2, width/2+10},
        {-width/2-10, width/2}
    };

    int orange_coord[4][2]={           //x,y, rotation
        {-width/2, -width/2-18},
        {width/2+18, -width/2},
        {width/2, width/2+18},
        {-width/2-18, width/2}
    };

    int green_coord[4][2]={           //x,y, rotation
        {-width/2, -width/2-26},
        {width/2+26, -width/2},
        {width/2, width/2+26},
        {-width/2-26, width/2}
    };



    for(int i=0; i<4; i++){     //create crossroad entrances
        road[i] = new Road(true);
        road[i]->setParentItem(this);
        road[i]->setPos(coord[i][0], coord[i][1]);
        road[i]->setRotation(coord[i][2]);
        road[i]->mL->isCrossroad = true;
        road[i]->mL->itemsCrossroad = this;

        red[i] = new Light(Qt::red);
        red[i]->setParentItem(this);
        red[i]->setPos(red_coord[i][0], red_coord[i][1]);

        orange[i] = new Light( QColor(255,128,0) );
        orange[i]->setParentItem(this);
        orange[i]->setPos(orange_coord[i][0], orange_coord[i][1]);

        green[i] = new Light(Qt::green);
        green[i]->setParentItem(this);
        green[i]->setPos(green_coord[i][0], green_coord[i][1]);

    }


    setFlags(QGraphicsItem::ItemIsMovable);

}

// 1-zielone
// 2-pomaranczowe
// 3-czerwone
// 4-pomaranczowe+czerwone

/**********************************************
 *  Funkcja wykonywana cyklicznie w ściśle określonych odstepach czasu, wykonująca "logikę" świateł na skrzyżowaniu
 */
void Crossroad::timerEvent(QTimerEvent *){
    if(timer>27)timer=0;

    if(timer>=0 && timer<10){
        // "ZIELONE  |  CZERWONE";
        setLight(1,3);
        stop_a=false;
        stop_b=true;
    }
    else if(timer>=10 && timer<11){
        // "POMARAŃCZOWE  |  CZERWONE";
        setLight(2,3);
        stop_a=true;
        stop_b=true;
    }
    else if(timer>=11 && timer<12){
        // "CZERWONE  |  CZERWONE";
        setLight(3,3);
        stop_a=true;
        stop_b=true;
    }
    else if(timer>=12 && timer<13){
        // "CZERWONE  |  CZERWONE+POMARAŃCZOWE";
        setLight(3,4);
        stop_a=true;
        stop_b=true;
    }
    else if(timer>=13 && timer<23){
        // "CZERWONE  |  ZIELONE";
        setLight(3,1);
        stop_a=true;
        stop_b=false;
    }
    else if(timer>=23 && timer<24){
        // "CZERWONE  |  POMARAŃCZOWE";
        setLight(3,2);
        stop_a=true;
        stop_b=true;
    }
    else if(timer>=25 && timer<26){
        // "CZERWONE  |  CZERWONE";
        setLight(3,3);
        stop_a=true;
        stop_b=true;
    }
    else if(timer>=26 && timer<27){
        // "POMARAŃCZOWE  |  CZERWONE";
        setLight(2,3);
        stop_a=true;
        stop_b=true;
    }
    update();



    timer++;
}

/**********************************************
 *  Zwraca wskaźnik do wjzdu dla podanego parametru
 *  @param entrance nazwa enum danego wjazdu
 */
Road* Crossroad::getEntrance(Entrance entrance)
{
    if(entrance==Entrance::North) return road[Entrance::North];
    else if(entrance==Entrance::East) return road[Entrance::East];
    else if(entrance==Entrance::South) return road[Entrance::South];
    else if(entrance==Entrance::West) return road[Entrance::West];
    else return NULL;
}

/**********************************************
 *  Zwraca następny cel dla pojazdów
 *  @param currentMilestone wskaźnik do wjazdu na którym znajduje się auto
 *  @param dir kierunek w którym chce skręcić
 */
Milestone* Crossroad::getNextMilestone(Milestone* currentMilestone, Direction dir)
{
    if( ((currentMilestone->itemsRoad == road[0] || currentMilestone->itemsRoad == road[2]) && stop_a == false)  ||  ((currentMilestone->itemsRoad == road[1] || currentMilestone->itemsRoad == road[3]) && stop_b == false) ){
        int temp;

        for(int i=0; i<4; i++){
            if(currentMilestone == road[i]->mL)
            {
                if(dir == Direction::left) temp = i+1;
                if(dir == Direction::right) temp = i-1;
                if(dir == Direction::straight) temp = i+2;
            }

        }

        if(temp<0) temp= temp+4;
        if(temp>3) temp=temp-4;
        return road[temp]->mP;

    }
    else{
    return NULL;
    }
}






/**********************************************
 *  Obszar rysowania obiektu
 */
QRectF Crossroad::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-width*2 - adjust, -width*2 - adjust,
                  4*width + adjust, 4*width + adjust);
}

/**********************************************
 *  Kształt obiektu służący do wykrywania kolizji
 */
QPainterPath Crossroad::shape() const
{
    QPainterPath path;
    path.addRect(-width/2, -width/2, width, width);
    return path;
}
/**********************************************
 *  Funkcja rysująca obiekt
 */
void Crossroad::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 0));
    painter->drawRect(-width/2, -width/2, width, width);
}


/**********************************************
 *  Zapala i gasi swiatla drogowe
 */
void Crossroad::setLight(int a, int b){
    // 1-zielone
    // 2-pomaranczowe
    // 3-czerwone
    // 4-pomaranczowe+czerwone
    // a-pierwsza para, b - druga para

    QColor r_on = QColor(255,0,0);
    QColor r_off = QColor(50,20,20);

    QColor o_on = QColor(255,128,0);
    QColor o_off = QColor(50,35,20);

    QColor g_on = QColor(0,255,0);
    QColor g_off = QColor(20,50,20);



    switch (a){
    case 1:
        red[0]->color = r_off;
        red[2]->color = r_off;
        orange[0]->color = o_off;
        orange[2]->color = o_off;
        green[0]->color = g_on;
        green[2]->color = g_on;
        break;
    case 2:
        red[0]->color = r_off;
        red[2]->color = r_off;
        orange[0]->color = o_on;
        orange[2]->color = o_on;
        green[0]->color = g_off;
        green[2]->color = g_off;
        break;
    case 3:
        red[0]->color = r_on;
        red[2]->color = r_on;
        orange[0]->color = o_off;
        orange[2]->color = o_off;
        green[0]->color = g_off;
        green[2]->color = g_off;
        break;
    case 4:
        red[0]->color = r_on;
        red[2]->color = r_on;
        orange[0]->color = o_on;
        orange[2]->color = o_on;
        green[0]->color = g_off;
        green[2]->color = g_off;
        break;
   default:
        red[0]->color = r_off;
        red[2]->color = r_off;
        orange[0]->color = o_off;
        orange[2]->color = o_off;
        green[0]->color = g_off;
        green[2]->color = g_off;
        break;
    }

    switch (b){
    case 1:
        red[1]->color = r_off;
        red[3]->color = r_off;
        orange[1]->color = o_off;
        orange[3]->color = o_off;
        green[1]->color = g_on;
        green[3]->color = g_on;
        break;
    case 2:
        red[1]->color = r_off;
        red[3]->color = r_off;
        orange[1]->color = o_on;
        orange[3]->color = o_on;
        green[1]->color = g_off;
        green[3]->color = g_off;
        break;
    case 3:
        red[1]->color = r_on;
        red[3]->color = r_on;
        orange[1]->color = o_off;
        orange[3]->color = o_off;
        green[1]->color = g_off;
        green[3]->color = g_off;
        break;
    case 4:
        red[1]->color = r_on;
        red[3]->color = r_on;
        orange[1]->color = o_on;
        orange[3]->color = o_on;
        green[1]->color = g_off;
        green[3]->color = g_off;
        break;
   default:
        red[1]->color = r_off;
        red[3]->color = r_off;
        orange[1]->color = o_off;
        orange[3]->color = o_off;
        green[1]->color = g_off;
        green[3]->color = g_off;
        break;
    }
}





















