#ifndef UNIT_H
#define UNIT_H
#include "element.h"



class Unit : public Element{
public:
    Unit();

    void move(Direction direction);

    int getHealthPoint() const;
    void setHealthPoint(int value);

    int getMaxHealthPoint() const;
    void setMaxHealthPoint(int value);

private:
    int healthPoint;
    int maxHealthPoint;
};

#endif // UNIT_H
