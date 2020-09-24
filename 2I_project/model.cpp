#include "model.h"
#include <QDebug>
Model::Model()
{
    this->player = new Player();
    this->map = new Map();
    this->boss = new Boss();
}

Player *Model::getPlayer() const
{
    return player;
}

void Model::setPlayer(Player *value)
{
    player = value;
}

Map *Model::getMap() const
{
    return map;
}

void Model::setMap(Map *value)
{
    map = value;
}

Boss *Model::getBoss() const
{
    return boss;
}

void Model::setBoss(Boss *value)
{
    boss = value;
}

void Model::resetModel(){
    this->player = new Player();
    this->map = new Map();
    this->boss = new Boss();
}
