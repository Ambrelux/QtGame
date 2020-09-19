#ifndef MODEL_H
#define MODEL_H
#include "player.h"
#include "map.h"
#include "enemy.h"

class Model
{
public:
    Model();

    class Player *getPlayer() const;
    void setPlayer(Player *value);

    Map *getMap() const;
    void setMap(Map *value);

    void resetModel();

    QVector<Enemy *> getEnemyList() const;
    void setEnemyList(const QVector<Enemy *> &value);

private:
    Player *player;
    Map *map;
    QVector<Enemy *> enemyList;
};

#endif // MODEL_H
