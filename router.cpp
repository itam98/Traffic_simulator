#include "router.h"


Router::Router()
{

}





void Router::connect(Road *road1, Road *road2)
{
    road1->mB->nextMilestone = road2->mB;
    road2->mB->prevMilestone = road1->mB;

    road2->mA->nextMilestone = road1->mA;
    road1->mA->prevMilestone = road2->mA;




}

