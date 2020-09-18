#include "enemy.h"


Enemy::Enemy()
{
    this->setXCoord(60*32);
    this->setYCoord(50*32);
    this->setXTile(60);
    this->setYTile(50);
    this->setTilePath(":/images/images/student/student_");
    this->setTile("default");
    this->setDirection(Direction::Down);
}
