#include "vehicle.h"

Vehicle::Vehicle()
{

}


qreal Vehicle::getSpeed(){
    return speed;
}


void Vehicle::setSpeed(qreal value)
{
    speed = value;      //ustaw ograniczenie prędkości
    step_length = value/framerate;       //oblicz jaki to da krok na jeden krok symulacji
    aproxDistanceToMS = qCeil(step_length/1.9); //wyzancz mLrgines błędu osiągnicia celu z dokładnością do +- pół kroku
    //qDebug()<< "setSpeed:"<<value;
}

void Vehicle::setDefaultSpeed(){
    setSpeed(defaultSpeed);

}

void Vehicle::setMilestone(Milestone *nextMS)
{
    currentMilestone = nextMS;
}

