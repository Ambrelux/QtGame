#include "view.h"
#include <QPointer>
#include <QtDebug>
extern Controller *pointerCtrl;

View::View(QWidget *parent)
{  
    this->scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
}

void View::keyPressEvent(QKeyEvent *event)
{

    switch(event->key()){
        case Qt::Key_Left:
            pointerCtrl->keyPressed("left");
            break;
        case Qt::Key_Right:
            pointerCtrl->keyPressed("right");
            break;
        case Qt::Key_Up:
            pointerCtrl->keyPressed("up");
            break;
        case Qt::Key_Down:
            pointerCtrl->keyPressed("down");
            break;
        case Qt::Key_Space:
            pointerCtrl->keyPressed("space");
            break;
    }
}

void View::displayMap(Player *player, Map *map)
{
    this->scene->setSceneRect(player->getXCoord()-400,player->getYCoord()-300,800,600);
    this->scene->setBackgroundBrush(QBrush(QImage(map->getMapImagePath())));
    this->setScene(scene);
}

void View::displayPlayer(Player *player)
{
    QGraphicsPixmapItem *pixmapPlayer = new QGraphicsPixmapItem(player->getTile());
    pixmapPlayer->setPos(player->getXCoord(),player->getYCoord());
    this->scene->addItem(pixmapPlayer);
}

void View::displayEnemy(QVector<Enemy *> enemyList)
{
    if(enemyList.size() > 0)
    {
        for(int i = 0 ; i < enemyList.size() ; i++)
        {
            QGraphicsPixmapItem *pixmapEnemy = new QGraphicsPixmapItem(enemyList[i]->getTile());
            pixmapEnemy->setPos(enemyList[i]->getXCoord(),enemyList[i]->getYCoord());
            this->scene->addItem(pixmapEnemy);
        }
    }
}

void View::displayProjectile(QVector<Projectile *>projectileList)
{       
    if(projectileList.size() > 0)
    {
        for(int i = 0 ; i < projectileList.size() ; i++)
        {
            QGraphicsPixmapItem *pixmapProjectile = new QGraphicsPixmapItem(projectileList[i]->getTile());
            pixmapProjectile->setPos(projectileList[i]->getXCoord(),projectileList[i]->getYCoord());
            this->scene->addItem(pixmapProjectile);
        }
    }    
}

void View::displayAmmo(QVector<Ammo *> ammoList)
{
    if(ammoList.size() > 0)
    {
        for(int i = 0 ; i < ammoList.size() ; i++)
        {
            QGraphicsPixmapItem *pixmapAmmo = new QGraphicsPixmapItem(ammoList[i]->getTile());
            pixmapAmmo->setPos(ammoList[i]->getXCoord(),ammoList[i]->getYCoord());
            this->scene->addItem(pixmapAmmo);
        }
    }
}

void View::displayCoffee(QVector<Coffee *> coffeeList)
{
    if(coffeeList.size() > 0)
    {
        for(int i = 0 ; i < coffeeList.size() ; i++)
        {
            QGraphicsPixmapItem *pixmapCoffee = new QGraphicsPixmapItem(coffeeList[i]->getTile());
            pixmapCoffee->setPos(coffeeList[i]->getXCoord(),coffeeList[i]->getYCoord());
            this->scene->addItem(pixmapCoffee);
        }
    }
}

void View::resetView()
{
    delete this->scene;
    this->scene = new QGraphicsScene();
}



