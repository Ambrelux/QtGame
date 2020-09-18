#include "player.h"
#include <QDebug>

Player::Player()
{
    this->setXCoord(66*32);
    this->setYCoord(57*32);
    this->setXTile(66);
    this->setYTile(57);
    this->setTilePath(":/images/images/player/player_");
    this->setTile("default");
    this->setDirection(Direction::Down);
    this->setProjectileQuantity(5);

}

unsigned int Player::getProjectileQuantity() const
{
    return projectileQuantity;
}

void Player::setProjectileQuantity(unsigned int value)
{
    projectileQuantity = value;
}

