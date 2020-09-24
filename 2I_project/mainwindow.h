#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
#include <QVector>
#include <QLabel>
#include "controller.h"
#include "enemy.h"
#include "ammo.h"
#include "projectile.h"
#include "coffee.h"
#include "homework.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //variables
    QGraphicsScene * scene;

    //function
    void keyPressEvent(QKeyEvent *event);
    void displayMap(Player *player, Map *map);
    void displayPlayer(Player *player);
    void displayEnemy(QVector<Enemy *>enemyList);
    void displayBoss(Boss *boss);
    void displayProjectile(QVector<Projectile *>projectileList);
    void displayAmmo(QVector<Ammo *>ammoList);
    void displayCoffee(QVector<Coffee *>coffeeList);
    void displayHomework(QVector<Homework *>homeworkList);
    void displayWin(QString text, QString color);
    void resetView();

private:
    Ui::MainWindow *ui;
    QLabel *label;
};

#endif // MAINWINDOW_H
