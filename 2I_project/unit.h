#ifndef UNIT_H
#define UNIT_H
#include "element.h"

enum class Direction {
    Up,Down,Left,Right

};

class Unit : public Element{
public:
    Unit();

    void move(Direction direction);

    int getHealthPoint() const;
    void setHealthPoint(int value);

    Direction getDirection() const;
    void setDirection(const Direction &value);

private:
    int healthPoint;
    Direction direction;
};

#endif // UNIT_H
