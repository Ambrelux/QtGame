#include "homework.h"

Homework::Homework(int _xTile, int _yTile)
{
    this->setXTile(_xTile);
    this->setYTile(_yTile);
    this->setXCoord(_xTile*32);
    this->setYCoord(_yTile*32);
    this->setTilePath(":/images/images/item/");
    this->setTile("homework");
}
