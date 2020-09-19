#include "enemy.h"


Enemy::Enemy(int _xTile, int _yTile, int _healthPoint, QString studentType)
{
    this->setXCoord(_xTile*32);
    this->setYCoord(_yTile*32);
    this->setXTile(_xTile);
    this->setYTile(_yTile);
    this->setTilePath(":/images/images/student/" + studentType);
    this->setTile("default");
    this->setDirection(Direction::Down);
    this->setHealthPoint(_healthPoint);
}
