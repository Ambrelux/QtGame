#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointer>
#include <QtDebug>
#include <QFontDatabase>
extern Controller *pointerCtrl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene();
    this->scene->setFocus();
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setFixedSize(960,490);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "prout";
    switch(event->key()){
        case Qt::Key_Q:
            pointerCtrl->keyPressed("left");
        break;
        case Qt::Key_D:
            pointerCtrl->keyPressed("right");
        break;
        case Qt::Key_Z:
            pointerCtrl->keyPressed("up");
        break;
        case Qt::Key_S:
            pointerCtrl->keyPressed("down");
        break;
        case Qt::Key_Space:
            pointerCtrl->keyPressed("space");
        break;
        case Qt::Key_A:
            pointerCtrl->keyPressed("a");
        break;
        case Qt::Key_R:
            pointerCtrl->keyPressed("r");
        break;
        case Qt::Key_M:
            pointerCtrl->keyPressed("m");
        break;

    }
}


void MainWindow::displayMap(Player *player, Map *map)
{
    this->scene->setSceneRect(player->getXCoord()-480,player->getYCoord()-245,960,490);
    this->scene->setBackgroundBrush(QBrush(QImage(map->getMapImagePath())));
    ui->view->setScene(scene);
}

void MainWindow::displayPlayer(Player *player)
{
    QGraphicsPixmapItem *pixmapPlayer = new QGraphicsPixmapItem(player->getTile());
    pixmapPlayer->setPos(player->getXCoord(),player->getYCoord());
    this->scene->addItem(pixmapPlayer);
}

void MainWindow::displayEnemy(QVector<Enemy *> enemyList)
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

void MainWindow::displayBoss(Boss *boss)
{
    QGraphicsPixmapItem *pixmapBoss = new QGraphicsPixmapItem(boss->getTile());
    pixmapBoss->setPos(boss->getXCoord(),boss->getYCoord());
    this->scene->addItem(pixmapBoss);
}

void MainWindow::displayProjectile(QVector<Projectile *>projectileList)
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

void MainWindow::displayAmmo(QVector<Ammo *> ammoList)
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

void MainWindow::displayCoffee(QVector<Coffee *> coffeeList)
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

void MainWindow::displayHomework(QVector<Homework *> homeworkList)
{
    if(homeworkList.size() > 0)
    {
        for(int i = 0 ; i < homeworkList.size() ; i++)
        {
            QGraphicsPixmapItem *pixmaphomework = new QGraphicsPixmapItem(homeworkList[i]->getTile());
            pixmaphomework->setPos(homeworkList[i]->getXCoord(),homeworkList[i]->getYCoord());
            this->scene->addItem(pixmaphomework);
        }
    }
}

void MainWindow::displayWin(QString text, QString color)
{
    this->label = new QLabel(this);
    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/title.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont titleFont(family);
    titleFont.setPointSize(100);
    this->label = new QLabel(this);
    this->label->setText(text);
    this->label->setFont(titleFont);
    this->label->adjustSize();
    this->label->setGeometry(0,0,960,540);
    this->label->setAlignment(Qt::AlignCenter);
    this->label->setStyleSheet("QLabel {color :" + color +"; }");
}

void MainWindow::resetView()
{
    delete this->scene;
    this->scene = new QGraphicsScene();
}
