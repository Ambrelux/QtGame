#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "model.h"
#include "view.h"
#include "enemy.h"
#include "projectile.h"
#include "coffee.h"
#include "ammo.h"
#include "homework.h"

using namespace std;

class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(class View *view, class Model *model);

    void startGame();
    void setModel(Model *value);
    Model *getModel() const;
    void keyPressed(QString key);

    void mapInitialization();
    int getFutureTile(int xTile, int yTile, Direction direction);

    void playerAttack();
    bool checkCollisionPlayerEnemy();
    void checkCollisionPlayerAmmo();
    void checkCollisionPlayerCoffee();

    void createProjectile(Direction direction);

    QVector<Projectile *> getProjectileList() const;
    void setProjectileList(const QVector<Projectile *> &value);
    bool checkMaxDistance(int xTile, int yTile, int xInitialTile, int yInitialTile, int maxDistance);
    void moveProjectiles();
    void removeProjectile(int vectPos);

    void checkCollisionProjectileEnemy();

    void randomLootOnEnemy(int xTile, int yTile);

    QVector<Enemy *> getEnemyList() const;
    void setEnemyList(const QVector<Enemy *> &value);
    void removeEnemy(int vectPos);

    QVector<Ammo *> getAmmoList() const;
    void setAmmoList(const QVector<Ammo *> &value);
    void removeAmmo(int vectPos);

    QVector<Coffee *> getCoffeeList() const;
    void setCoffeeList(const QVector<Coffee *> &value);
    void removeCoffee(int vectPos);

    QVector<Homework *> getHomeworkList() const;
    void setHomeworkList(const QVector<Homework *> &value);
    void removeHomework(int vectPos);

public slots:
    void updateGame();

private:
    Model *model;
    View *view;
    QTimer *timer;
    QVector<Projectile *> projectileList;
    QVector<Enemy *> enemyList;
    QVector<Ammo *> ammoList;
    QVector<Coffee *> coffeeList;
    QVector<Homework *> homeworkList;
};

#endif // CONTROLLER_H
