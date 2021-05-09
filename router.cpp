#include "router.h"


Router::Router()
{

}





void Router::connect(Road *road1, Road *road2, bool inv1, bool inv2)
{
    if(inv1==false && inv2==false){
        road1->mB->nextMilestone = road2->mB;
        road2->mB->prevMilestone = road1->mB;

        road2->mA->nextMilestone = road1->mA;
        road1->mA->prevMilestone = road2->mA;
    }

    if(inv1==false && inv2==true){
        road1->mB->nextMilestone = road2->mA;
        road2->mA->prevMilestone = road1->mB;

        road2->mB->nextMilestone = road1->mA;
        road1->mA->prevMilestone = road2->mB;
    }
    //TODO: dodać pozostałe przypadki


}

