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

void View::resetView()
{
    delete this->scene;
    this->scene = new QGraphicsScene();
}



