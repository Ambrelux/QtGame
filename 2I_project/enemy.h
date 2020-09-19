#ifndef ENEMY_H
#define ENEMY_H
#include "unit.h"

class Enemy : public Unit
{
public:
    Enemy(int _xTile, int _yTile, int _healthPoint, QString studentType);
};

#endif // ENEMY_H
