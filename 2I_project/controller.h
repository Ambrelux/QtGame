#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "model.h"
#include "mainwindow.h"
#include "menu.h"
#include "enemy.h"
#include "projectile.h"
#include "coffee.h"
#include "ammo.h"
#include "homework.h"
#include "rules.h"
using namespace std;

class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(class MainWindow *view, class Model *model, class Menu *menu, class Rules *rules);

    void startGame();

    void mapInitialization();

    bool checkTile(int xTile, int yTile, Direction direction);

    void playerAttack();

    bool checkCollisionPlayerEnemy();
    bool checkCollisionPlayerBoss();
    bool checkCollisionEnemyPlayer(int xTile, int yTile, Direction direction);
    bool checkCollisionEnemyEnemy(int xTile, int yTile, Direction direction);
    bool checkCollisionEnemyBoss(int xTile, int yTile, Direction direction);
    void checkCollisionPlayerAmmo();
    void checkCollisionPlayerCoffee();
    void checkCollisionPlayerHomework();
    void checkCollisionProjectile();

    void createProjectile(int xTile, int yTile, Direction direction);
    void moveProjectiles();
    void randomLootOnEnemy(int xTile, int yTile);
    bool checkMaxDistance(int xTile, int yTile, int xInitialTile, int yInitialTile, int maxDistance);
    void moveEnemies();

    // GETTERS SETTERS REMOVERS

    QVector<Projectile *> getProjectileList() const;
    void setProjectileList(const QVector<Projectile *> &value);
    void removeProjectile(int vectPos);

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

    int getTimeIterator() const;
    void setTimeIterator(int value);

    void setModel(Model *value);
    Model *getModel() const;


    void endGame();
    void delay(int i);
    void resetList();
    void showRules();
    void showMenu();
    void keyPressed(QString key);

    int state;

public slots:
    void updateGame();

private:
    Model *model;
    MainWindow *view;
    Menu *menu;
    Rules *rules;

    QVector<Projectile *> projectileList;
    QVector<Enemy *> enemyList;
    QVector<Ammo *> ammoList;
    QVector<Coffee *> coffeeList;
    QVector<Homework *> homeworkList;


    QMediaPlayer whistleSound;
    QMediaPlayer screamSound;
    QMediaPlayer drinkSound;
    QMediaPlayer bgMusic;

    QTimer *timer;
    int timeIterator;
};

#endif // CONTROLLER_H
