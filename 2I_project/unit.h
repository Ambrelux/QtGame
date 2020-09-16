#ifndef UNIT_H
#define UNIT_H
#include "element.h"

class Unit : public Element{
public:
    Unit();
    int getHealthPoint() const;
    void setHealthPoint(int value);
    void move(QString direction);

private:
    int healthPoint;
};

#endif // UNIT_H
