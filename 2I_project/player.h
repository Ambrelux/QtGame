#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"
#include <QKeyEvent>

class Player : public Unit{
public:
    Player();
    unsigned int getProjectileQuantity() const;
    void setProjectileQuantity(unsigned int value);

    unsigned int getHomeworkQuantity() const;
    void setHomeworkQuantity(unsigned int value);

private:
    unsigned int projectileQuantity;
    unsigned int homeworkQuantity;
};

#endif // PLAYER_H
