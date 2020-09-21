#include "controller.h"
#include <QtDebug>
Controller::Controller(View *view, Model *model)
{
    QVector<Enemy *> vect = this->getEnemyList();
    vect.push_back(new Enemy(60,50,5,"enemy_"));
    vect.push_back(new Enemy(55,50,5,"student_"));
    this->setEnemyList(vect);

    this->view = view;
    this->model = model;
    this->timer =  new QTimer();
    timer->connect(timer,SIGNAL(timeout()), this, SLOT(updateGame()));
}

void Controller::startGame(){
    this->mapInitialization();
    updateGame();
    this->view->show();
}

void Controller::updateGame()
{
    this->view->resetView();
    this->view->displayMap(this->getModel()->getPlayer(),this->getModel()->getMap());
    this->view->displayPlayer(this->getModel()->getPlayer());
    this->moveProjectiles();
    this->checkCollisionProjectileEnemy();
    this->view->displayProjectile(this->getProjectileList());
    this->view->displayEnemy(this->getEnemyList());
    timer->start(10);
}


void Controller::keyPressed(QString key)
{

    if(key == "up")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Up);
        if(canPlayerMove(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection())))
        {
            this->model->getPlayer()->move(this->model->getPlayer()->getDirection());
        }

    }
    else if(key == "down")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Down);
        if(canPlayerMove(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection())))
        {
            this->model->getPlayer()->move(this->model->getPlayer()->getDirection());
        }
    }
    else if(key == "left")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Left);
        if(canPlayerMove(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection())))
        {
            this->model->getPlayer()->move(this->model->getPlayer()->getDirection());
        }
    }
    else if(key == "right")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Right);
        if(canPlayerMove(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection())))
        {
            this->model->getPlayer()->move(this->model->getPlayer()->getDirection());
        }
    }
    else if(key == "space")
    {
        if(this->model->getPlayer()->getProjectileQuantity() > 0)
        {
            this->model->getPlayer()->setProjectileQuantity(this->model->getPlayer()->getProjectileQuantity() - 1);
            this->createProjectile(this->model->getPlayer()->getDirection());
        }

    }

}

void Controller::mapInitialization()
{
    QFile file(this->getModel()->getMap()->getFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QVector<QString> _mapMatrix;
    QString line;

    while(! stream.atEnd())
    {
        line = stream.readLine();
        _mapMatrix.append(line);
    }
    this->getModel()->getMap()->setMapMatrix(_mapMatrix);
}

int Controller::getFutureTile(int xTile, int yTile, Direction direction)
{
    QString futureTile;
    bool ok;

    if(direction == Direction::Up)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile-1).at(xTile);
        return futureTile.toInt(&ok,10);
    }
    else if(direction == Direction::Down){
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile+1).at(xTile);
        return futureTile.toInt(&ok,10);
    }
    else if(direction == Direction::Left)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile).at(xTile-1);
        return futureTile.toInt(&ok,10);
    }
    else if(direction == Direction::Right)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile).at(xTile+1);
        return futureTile.toInt(&ok,10);
    }

    return 0;
}

bool Controller::canPlayerMove(int futureTile)
{
    if(futureTile == 1 && !checkCollisionPlayerEnemy())
    {
        return true;
    }
    else if(futureTile == 0 || checkCollisionPlayerEnemy())
    {
        return false;
    }

    return false;
}

bool Controller::checkCollisionPlayerEnemy()
{
    if(this->getEnemyList().size() > 0)
    {
        for(int i = 0 ; i < this->getEnemyList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() - 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Down && this->getModel()->getPlayer()->getYTile() + 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                return true;
            }
        }
    }

    return false;
}

void Controller::createProjectile(Direction direction)
{
    if(direction == Direction::Up)
    {
        QVector<Projectile *> vect = this->getProjectileList();
        vect.push_back(new Projectile(this->model->getPlayer()->getXTile(),this->model->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()));
        this->setProjectileList(vect);
    }
    else if (direction == Direction::Down)
    {
        QVector<Projectile *> vect = this->getProjectileList();
        vect.push_back(new Projectile(this->model->getPlayer()->getXTile(),this->model->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()));
        this->setProjectileList(vect);
    }
    else if (direction == Direction::Left)
    {
        QVector<Projectile *> vect = this->getProjectileList();
        vect.push_back(new Projectile(this->model->getPlayer()->getXTile(),this->model->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()));
        this->setProjectileList(vect);
    }
    else if (direction == Direction::Right)
    {
        QVector<Projectile *> vect = this->getProjectileList();
        vect.push_back(new Projectile(this->model->getPlayer()->getXTile(),this->model->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()));
        this->setProjectileList(vect);
    }
}

void Controller::moveProjectiles()
{
    if(this->getProjectileList().size() > 0)
    {
        for(int i = 0 ; i < this->getProjectileList().size() ; i++)
        {
            if(getFutureTile(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getDirection()) && checkMaxDistance(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getInitialXTile(),this->getProjectileList()[i]->getInitialYTile(),this->getProjectileList()[i]->getMaxDistance()))
            {
                if(this->getProjectileList()[i]->getDirection() == Direction::Up)
                {
                    this->getProjectileList()[i]->setYTile(this->getProjectileList()[i]->getYTile() - 1);
                    this->getProjectileList()[i]->setYCoord(this->getProjectileList()[i]->getYCoord() - 32);
                }
                else if (this->getProjectileList()[i]->getDirection() == Direction::Down)
                {
                    this->getProjectileList()[i]->setYTile(this->getProjectileList()[i]->getYTile() + 1);
                    this->getProjectileList()[i]->setYCoord(this->getProjectileList()[i]->getYCoord() + 32);
                }
                else if (this->getProjectileList()[i]->getDirection() == Direction::Left)
                {
                    this->getProjectileList()[i]->setXTile(this->getProjectileList()[i]->getXTile() - 1);
                    this->getProjectileList()[i]->setXCoord(this->getProjectileList()[i]->getXCoord() - 32);
                }
                else if (this->getProjectileList()[i]->getDirection() == Direction::Right)
                {
                    this->getProjectileList()[i]->setXTile(this->getProjectileList()[i]->getXTile() + 1);
                    this->getProjectileList()[i]->setXCoord(this->getProjectileList()[i]->getXCoord() + 32);
                }
            }
            else if (!getFutureTile(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getDirection()) || !checkMaxDistance(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getInitialXTile(),this->getProjectileList()[i]->getInitialYTile(),this->getProjectileList()[i]->getMaxDistance()))
            {
                removeProjectile(i);
            }
        }
    }
}



void Controller::checkCollisionProjectileEnemy()
{
    if(this->getProjectileList().size() > 0)
    {
        for(int i = 0 ; i < this->getProjectileList().size() ; i++)
        {
            if(this->getEnemyList().size() > 0)
            {
                for(int j = 0 ; j < this->getEnemyList().size() ; j++)
                {
                    if(this->getProjectileList()[i]->getXTile() == this->getEnemyList()[j]->getXTile() && this->getProjectileList()[i]->getYTile() == this->getEnemyList()[j]->getYTile())
                    {
                        removeProjectile(i);
                        removeEnemy(j);
                    }
                }
            }

        }

    }
}


QVector<Enemy *> Controller::getEnemyList() const
{
    return enemyList;
}

void Controller::setEnemyList(const QVector<Enemy *> &value)
{
    enemyList = value;
}

void Controller::removeEnemy(int vectPos)
{
    delete this->enemyList[vectPos];
    this->enemyList.erase(this->enemyList.begin() + vectPos);
}

QVector<Projectile *> Controller::getProjectileList() const
{
    return projectileList;
}

void Controller::setProjectileList(const QVector<Projectile *> &value)
{
    projectileList = value;
}

void Controller::removeProjectile(int vectPos)
{
    delete this->projectileList[vectPos];
    this->projectileList.erase(this->projectileList.begin() + vectPos);
}

bool Controller::checkMaxDistance(int xTile, int yTile, int xInitialTile, int yInitialTile, int maxDistance)
{
    int diffX = xTile - xInitialTile;
    int diffY = yTile - yInitialTile;

    if(diffX < maxDistance && diffX > - maxDistance && diffY < maxDistance && diffY > - maxDistance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Controller::setModel(Model *value)
{
    model = value;
}

Model *Controller::getModel() const
{
    return model;
}

