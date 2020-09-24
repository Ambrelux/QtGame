#ifndef MODEL_H
#define MODEL_H
#include "player.h"
#include "map.h"
#include "boss.h"

class Model
{
public:
    Model();

    class Player *getPlayer() const;
    void setPlayer(Player *value);

    Map *getMap() const;
    void setMap(Map *value);

    Boss *getBoss() const;
    void setBoss(Boss *value);

    void resetModel();

private:
    Player *player;
    Map *map;
    Boss *boss;

};

#endif // MODEL_H
