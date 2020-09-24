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

    float getMaxHealthPoint() const;
    void setMaxHealthPoint(float value);

private:
    unsigned int projectileQuantity;
    unsigned int homeworkQuantity;
    float maxHealthPoint;
};

#endif // PLAYER_H
