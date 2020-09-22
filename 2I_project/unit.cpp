#include "unit.h"
#include <QDebug>
Unit::Unit()
{

}

float Unit::getHealthPoint() const
{
    return healthPoint;
}

void Unit::setHealthPoint(float value)
{
    healthPoint = value;
}

float Unit::getMaxHealthPoint() const
{
    return maxHealthPoint;
}

void Unit::setMaxHealthPoint(float value)
{
    maxHealthPoint = value;
}

void Unit::move()
{

    if(this->getDirection() == Direction::Up){
        this->setYCoord(this->getYCoord()-32);
        this->setYTile(this->getYTile()-1);
    }
    else if(this->getDirection() == Direction::Down){
        this->setYCoord(this->getYCoord()+32);
        this->setYTile(this->getYTile()+1);
    }
    else if(this->getDirection() == Direction::Left){
        this->setXCoord(this->getXCoord()-32);
        this->setXTile(this->getXTile()-1);
    }
    else if(this->getDirection() == Direction::Right){
        this->setXCoord(this->getXCoord()+32);
        this->setXTile(this->getXTile()+1);
    }
}

