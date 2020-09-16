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
        //qDebug() << this->getYCoord();
        //this->setPos(this->pos().x(),this->pos().y()-32);
    }
    else if(direction == "down"){
        this->setYCoord(this->getYCoord()+32);
        //this->setPos(this->pos().x(),this->pos().y()+32);
    }
    else if(direction == "left"){
        this->setXCoord(this->getXCoord()-32);
        //this->setPos(this->pos().x()-32,this->pos().y());
    }
    else if(direction == "right"){
        this->setXCoord(this->getXCoord()+32);
        //this->setPos(this->pos().x()+32,this->pos().y());
    }
}
