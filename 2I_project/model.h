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

private:
    Player *player;
    Map *map;

};

#endif // MODEL_H
