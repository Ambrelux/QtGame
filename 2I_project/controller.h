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
    void moveProjectile();
    void removeProjectile(int vectPos);

    QVector<Projectile *> getProjectileList() const;
    void setProjectileList(const QVector<Projectile *> &value);

public slots:
    void updateGame();

private:
    Model *model;
    View *view;
    QTimer *timer;
    QVector<Projectile *> projectileList;
};

#endif // CONTROLLER_H
