#include "boss.h"


Boss::Boss()
{
    this->setHealthPoint(10);
    this->setXTile(83);
    this->setYTile(34);
    this->setXCoord(83*32);
    this->setYCoord(34*32);
    this->setDirection(Direction::Left);
    this->setTilePath(":/images/images/boss/boss_");
    this->setTile("default");
}
