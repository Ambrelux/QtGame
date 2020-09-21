#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QKeyEvent>

#include "model.h"
#include "view.h"
#include "projectile.h"
class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(class View *view, class Model *model);
    //~Controller();

    void startGame();
    void setModel(Model *value);
    Model *getModel() const;
    void keyPressed(QString key);

    void mapInitialization();
    int getFutureTile(int xTile, int yTile, Direction direction);
    bool canPlayerMove(int futureTile);
    bool checkCollisionPlayerEnemy();


    void createProjectile(Direction direction);

    QVector<Projectile *> getProjectileList() const;
    void setProjectileList(const QVector<Projectile *> &value);
    bool checkMaxDistance(int xTile, int yTile, int xInitialTile, int yInitialTile, int maxDistance);
    void moveProjectiles();
    void removeProjectile(int vectPos);

    void checkCollisionProjectileEnemy();

    QVector<Enemy *> getEnemyList() const;
    void setEnemyList(const QVector<Enemy *> &value);
    void removeEnemy(int vectPos);

public slots:
    void updateGame();

private:
    Model *model;
    View *view;
    QTimer *timer;
    QVector<Projectile *> projectileList;
    QVector<Enemy *> enemyList;
};

#endif // CONTROLLER_H
