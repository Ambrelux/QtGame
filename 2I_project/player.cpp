#include "player.h"
#include <QDebug>

Player::Player()
{
    this->setXCoord(400);
    this->setYCoord(500);
    this->setTile("default");
}


//void Player::keyPressEvent(QKeyEvent *event)
//{
//        if (event->key() == Qt::Key_Left){
//            setPos(x()-32,y());
//            setPixmap(QPixmap(":/images/images/player_left"));
//        }
//        else if (event->key() == Qt::Key_Right){
//            setPos(x()+32,y());
//            setPixmap(QPixmap(":/images/images/player_right"));
//            game->scene->setSceneRect(400,500,800,600);
//        }
//        else if (event->key() == Qt::Key_Up){
//            setPos(x(),y()-32);
//            setPixmap(QPixmap(":/images/images/player_up"));

//        }
//        else if (event->key() == Qt::Key_Down){
//            setPos(x(),y()+32);
//            setPixmap(QPixmap(":/images/images/player_default"));
//        }

//}
