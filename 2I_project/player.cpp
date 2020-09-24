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
    this->setMaxHealthPoint(5);
    this->setHealthPoint(this->getMaxHealthPoint());
    this->setHomeworkQuantity(0);

}

unsigned int Player::getProjectileQuantity() const
{
    return projectileQuantity;
}

void Player::setProjectileQuantity(unsigned int value)
{
    projectileQuantity = value;
}

unsigned int Player::getHomeworkQuantity() const
{
    return homeworkQuantity;
}

void Player::setHomeworkQuantity(unsigned int value)
{
    homeworkQuantity = value;
}

float Player::getMaxHealthPoint() const
{
    return maxHealthPoint;
}

void Player::setMaxHealthPoint(float value)
{
    maxHealthPoint = value;
}

