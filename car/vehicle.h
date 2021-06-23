#ifndef VEHICLE_H
#define VEHICLE_H

#include <QColor>
#include "../map/milestone.h"
#include <qmath.h>
#include <complex>

class Vehicle
{
public:
    Vehicle();

    void setMilestone(Milestone *nextMS);
    qreal framerate = 60; //ilość kroków symulacji na sekundę
    void setSpeed(qreal value);
    qreal getSpeed();
    void setDefaultSpeed();


protected:
    qreal defaultSpeed;
    qreal direction = 0;
    qreal speed = 0;
    qreal step_length = 0;
    Milestone *currentMilestone;
    int aproxDistanceToMS;
};

#endif // VEHICLE_H
