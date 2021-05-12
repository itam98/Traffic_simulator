#include "router.h"


Router::Router()
{

}





void Router::connect(Road *road1, Road *road2, bool inv1, bool inv2)
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


}

