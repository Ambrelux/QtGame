#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "resource.h"
#include "unit.h"

class Projectile : public Resource
{
public:
    Projectile(int _xTile, int _yTile);
    bool moveProjectile(Direction direction);

    int getInitialXTile() const;
    void setInitialXTile(int value);

    int getInitialYTile() const;
    void setInitialYTile(int value);

    int getMaxDistance() const;
    void setMaxDistance(int value);

private:
    int initialXTile;
    int initialYTile;
    int maxDistance;
};

#endif // PROJECTILE_H
