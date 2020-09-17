#include "model.h"

Model::Model()
{
    this->player = new Player();
    this->map = new Map();
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

void Model::resetModel(){
    this->player = new Player();
    this->map = new Map();
}
