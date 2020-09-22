#ifndef ENEMY_H
#define ENEMY_H
#include "unit.h"

class Enemy : public Unit
{
public:
    Enemy(int _xTile, int _yTile, int _healthPoint, QString studentType);
    int getNbMove() const;
    void setNbMove(int value);

private:
    int nbMove;
};

#endif // ENEMY_H
