#include "player.h"
#include <QDebug>

Player::Player()
{
    this->setXCoord(66*32);
    this->setYCoord(57*32);
    this->setXTile(66);
    this->setYTile(57);
    this->setTilePath(":/images/images/player_");
    this->setTile("up");
    this->setDirection(Direction::Up);

}

