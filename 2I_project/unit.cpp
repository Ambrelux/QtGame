#include "unit.h"
#include <QDebug>
Unit::Unit()
{

}

int Unit::getHealthPoint() const
{
    return healthPoint;
}

void Unit::setHealthPoint(int value)
{
    healthPoint = value;
}

void Unit::move(QString direction)
{

    if(direction == "up"){
        this->setYCoord(this->getYCoord()-32);
    }
    else if(direction == "down"){
        this->setYCoord(this->getYCoord()+32);
    }
    else if(direction == "left"){
        this->setXCoord(this->getXCoord()-32);
    }
    else if(direction == "right"){
        this->setXCoord(this->getXCoord()+32);
    }
}
