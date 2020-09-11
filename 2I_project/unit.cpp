#include "unit.h"

Unit::Unit(Element *parent)
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
