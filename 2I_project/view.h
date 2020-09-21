#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
#include <QVector>
#include "controller.h"
#include "enemy.h"
#include "ammo.h"
#include "projectile.h"
#include "coffee.h"
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    //~View();

    //variables
    QGraphicsScene * scene;

    //function
    void keyPressEvent(QKeyEvent *event);
    void displayMap(Player *player, Map *map);
    void displayPlayer(Player *player);
    void displayEnemy(QVector<Enemy *>enemyList);
    void displayProjectile(QVector<Projectile *>projectileList);
    void displayAmmo(QVector<Ammo *>ammoList);
    void displayCoffee(QVector<Coffee *>coffeeList);

    void resetView();
private:

};

#endif // VIEW_H
