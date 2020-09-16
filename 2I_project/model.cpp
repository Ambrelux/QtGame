#include "model.h"
#include "player.h"
Model::Model()
{
    this->player = new Player();
}

Player *Model::getPlayer() const
{
    return player;
}

void Model::setPlayer(Player *value)
{
    player = value;
}

void Model::resetModel(){
    this->player = new Player();
}
