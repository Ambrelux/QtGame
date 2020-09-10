#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"
#include <QKeyEvent>

class Player : public Unit{
public:
    Player(Unit * parent = 0);
    void keyPressEvent(QKeyEvent * event);
};

#endif // PLAYER_H
