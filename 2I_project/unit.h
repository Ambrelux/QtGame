#ifndef UNIT_H
#define UNIT_H
#include "element.h"



class Unit : public Element{
public:
    Unit();

    void move(Direction direction);

    int getHealthPoint() const;
    void setHealthPoint(int value);

private:
    int healthPoint;
};

#endif // UNIT_H
