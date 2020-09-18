#include "projectile.h"

Projectile::Projectile(int _xTile, int _yTile)
{
    this->setXTile(_xTile);
    this->setYTile(_yTile);

    this->setInitialXTile(_xTile);
    this->setInitialYTile(_yTile);

    this->setXCoord(_xTile*32);
    this->setYCoord(_yTile*32);

    this->setTilePath(":/images/images/item/");
    this->setTile("projectile");
    this->setMaxDistance(3);

}

bool Projectile::moveProjectile(Direction direction)
{
    int diffX = this->getXTile() - this->getInitialXTile();
    int diffY = this->getYTile() - this->getInitialYTile();

    if(diffX < this->getMaxDistance() && diffX > - this->getMaxDistance() && diffY < this->getMaxDistance() && diffY > - this->getMaxDistance())
    {
        if(direction == Direction::Up)
        {
            this->setYTile(this->getYTile() - 1);
            this->setYCoord(this->getYCoord() - 32);
            return true;
        }
        else if (direction == Direction::Down)
        {
            this->setYTile(this->getYTile() + 1);
            this->setYCoord(this->getYCoord() + 32);
            return true;
        }
        else if (direction == Direction::Left)
        {
            this->setXTile(this->getXTile() - 1);
            this->setXCoord(this->getXCoord() - 32);
            return true;
        }
        else if (direction == Direction::Right)
        {
            this->setXTile(this->getXTile() + 1);
            this->setXCoord(this->getXCoord() + 32);
            return true;
        }
    }

    return false;
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
