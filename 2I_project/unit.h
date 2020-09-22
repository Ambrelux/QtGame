#ifndef UNIT_H
#define UNIT_H
#include "element.h"



class Unit : public Element{
public:
    Unit();

    void move();

    float getHealthPoint() const;
    void setHealthPoint(float value);

    float getMaxHealthPoint() const;
    void setMaxHealthPoint(float value);

private:
    float healthPoint;
    float maxHealthPoint;
};

#endif // UNIT_H
