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

void Unit::move(Direction direction)
{

    if(direction == Direction::Up){
        this->setYCoord(this->getYCoord()-32);
        this->setYTile(this->getYTile()-1);
    }
    else if(direction == Direction::Down){
        this->setYCoord(this->getYCoord()+32);
        this->setYTile(this->getYTile()+1);
    }
    else if(direction == Direction::Left){
        this->setXCoord(this->getXCoord()-32);
        this->setXTile(this->getXTile()-1);
    }
    else if(direction == Direction::Right){
        this->setXCoord(this->getXCoord()+32);
        this->setXTile(this->getXTile()+1);
    }
}

