#include "model.h"
#include <QDebug>
Model::Model()
{
    this->player = new Player();
    this->map = new Map();

    // create new enemies

    QVector<Enemy *> vect = this->getEnemyList();
    vect.push_back(new Enemy(60,50,5,"enemy_"));
    vect.push_back(new Enemy(55,50,5,"student_"));
    this->setEnemyList(vect);
    qDebug() << this->getEnemyList().size();
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

QVector<Enemy *> Model::getEnemyList() const
{
    return enemyList;
}

void Model::setEnemyList(const QVector<Enemy *> &value)
{
    enemyList = value;
}
