#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"
#include <QKeyEvent>

class Player : public Unit{
public:
    Player();
    unsigned int getProjectileQuantity() const;
    void setProjectileQuantity(unsigned int value);

private:
    unsigned int projectileQuantity;
};

#endif // PLAYER_H
