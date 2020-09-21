#include "projectile.h"

Projectile::Projectile(int _xTile, int _yTile, Direction _direction)
{
    this->setXTile(_xTile);
    this->setYTile(_yTile);

    this->setInitialXTile(_xTile);
    this->setInitialYTile(_yTile);

    this->setXCoord(_xTile*32);
    this->setYCoord(_yTile*32);

    this->setTilePath(":/images/images/item/");
    this->setTile("homework");

    this->setDirection(_direction);

    this->setMaxDistance(3);

}

int Projectile::getInitialXTile() const
{
    return initialXTile;
}

void Projectile::setInitialXTile(int value)
{
    initialXTile = value;
}

int Projectile::getInitialYTile() const
{
    return initialYTile;
}

void Projectile::setInitialYTile(int value)
{
    initialYTile = value;
}

int Projectile::getMaxDistance() const
{
    return maxDistance;
}

void Projectile::setMaxDistance(int value)
{
    maxDistance = value;
}
