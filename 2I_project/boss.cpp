#include "boss.h"


Boss::Boss()
{
    this->setHealthPoint(10);
    this->setXTile(90);
    this->setYTile(22);
    this->setXCoord(90*32);
    this->setYCoord(22*32);
    this->setDirection(Direction::Down);
    this->setTilePath(":/images/images/boss/boss_");
    this->setTile("down");
}
