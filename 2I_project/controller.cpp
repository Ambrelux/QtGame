#include "controller.h"
#include <QtDebug>
Controller::Controller(View *view, Model *model)
{
    srand((unsigned) time(0));
    this->view = view;
    this->model = model;
    this->timer =  new QTimer();
    timer->connect(timer,SIGNAL(timeout()), this, SLOT(updateGame()));
    this->whistleSound.setMedia(QUrl("qrc:/sounds/sounds/whistle.wav"));
    this->screamSound.setMedia(QUrl("qrc:/sounds/sounds/scream.wav"));
    this->setTimeIterator(0);
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
    this->moveProjectiles();
    this->setTimeIterator(this->getTimeIterator() + 1);
    if(this->getTimeIterator()>10)
    {
        moveEnemies();
        this->setTimeIterator(0);
    }
    this->checkCollisionProjectileEnemy();
    this->checkCollisionPlayerAmmo();
    this->checkCollisionPlayerCoffee();
    this->checkCollisionPlayerHomework();
    this->view->displayProjectile(this->getProjectileList());
    this->view->displayEnemy(this->getEnemyList());
    this->view->displayAmmo(this->getAmmoList());
    this->view->displayCoffee(this->getCoffeeList());
    this->view->displayHomework(this->getHomeworkList());
    this->view->displayPlayer(this->getModel()->getPlayer());

    timer->start(10);
}

void Controller::keyPressed(QString key)
{

    if(key == "up")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Up);
        if(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy())
        {
            this->model->getPlayer()->move();
        }

    }
    else if(key == "down")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Down);
        if(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy())
        {
            this->model->getPlayer()->move();
        }
    }
    else if(key == "left")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Left);
        if(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy())
        {
            this->model->getPlayer()->move();
        }
    }
    else if(key == "right")
    {
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->setDirection(Direction::Right);
        if(getFutureTile(this->model->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->model->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy())
        {
            this->model->getPlayer()->move();
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
    else if(key == "a")
    {
        whistleSound.play();
        playerAttack();
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint()- 0.5);
    }

}

void Controller::mapInitialization()
{
    QFile file(this->getModel()->getMap()->getFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QVector<QString> _mapMatrix;
    QString line;
    QVector<Enemy *> vectEnemy = this->getEnemyList();
    QVector<Homework *> vectHomework = this->getHomeworkList();

    while(! stream.atEnd())
    {
        line = stream.readLine();
        _mapMatrix.append(line);
    }
    this->getModel()->getMap()->setMapMatrix(_mapMatrix);

    for(int i = 0 ; i < this->model->getMap()->getMapMatrix().size() ; i++)
    {
        for (int j = 0 ; j < this->model->getMap()->getMapMatrix().at(i).size() ; j++)
        {
            if(this->model->getMap()->getMapMatrix().at(i).at(j) == "s")
            {
                vectEnemy.append(new Enemy(j,i,2,"student_"));
            }
            else if(this->model->getMap()->getMapMatrix().at(i).at(j) == "e")
            {
                vectEnemy.append(new Enemy(j,i,4,"enemy_"));
            }
            else if(this->model->getMap()->getMapMatrix().at(i).at(j) == "p")
            {
                vectHomework.append(new Homework(j,i));
            }
        }
    }

    this->setEnemyList(vectEnemy);
    this->setHomeworkList(vectHomework);
}

bool Controller::getFutureTile(int xTile, int yTile, Direction direction)
{
    QString futureTile;

    if(direction == Direction::Up)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile-1).at(xTile);
    }
    else if(direction == Direction::Down){
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile+1).at(xTile);
    }
    else if(direction == Direction::Left)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile).at(xTile-1);
    }
    else if(direction == Direction::Right)
    {
        futureTile = this->getModel()->getMap()->getMapMatrix().at(yTile).at(xTile+1);
    }

    if(futureTile != "0")
    {
        return true;
    }

    return false;
}

void Controller::playerAttack()
{
    if(this->getEnemyList().size() > 0)
    {
        for(int i = 0 ; i < this->getEnemyList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() - 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->getEnemyList()[i]->setHealthPoint(this->getEnemyList()[i]->getHealthPoint()-2);
                if(this->getEnemyList()[i]->getHealthPoint()<=0)
                {
                    randomLootOnEnemy(this->getEnemyList()[i]->getXTile(),this->getEnemyList()[i]->getYTile());
                    removeEnemy(i);
                }
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Down && this->getModel()->getPlayer()->getYTile() + 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->getEnemyList()[i]->setHealthPoint(this->getEnemyList()[i]->getHealthPoint()-2);
                if(this->getEnemyList()[i]->getHealthPoint()<=0)
                {
                    randomLootOnEnemy(this->getEnemyList()[i]->getXTile(),this->getEnemyList()[i]->getYTile());
                    removeEnemy(i);
                }
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->getEnemyList()[i]->setHealthPoint(this->getEnemyList()[i]->getHealthPoint()-2);
                if(this->getEnemyList()[i]->getHealthPoint()<=0)
                {
                    randomLootOnEnemy(this->getEnemyList()[i]->getXTile(),this->getEnemyList()[i]->getYTile());
                    removeEnemy(i);
                }
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->getEnemyList()[i]->setHealthPoint(this->getEnemyList()[i]->getHealthPoint()-2);
                if(this->getEnemyList()[i]->getHealthPoint()<=0)
                {
                    randomLootOnEnemy(this->getEnemyList()[i]->getXTile(),this->getEnemyList()[i]->getYTile());
                    removeEnemy(i);
                }
            }

        }

    }
}




bool Controller::checkCollisionPlayerEnemy()
{
    if(this->getEnemyList().size() > 0)
    {
        for(int i = 0 ; i < this->getEnemyList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() - 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Down && this->getModel()->getPlayer()->getYTile() + 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
                return true;
            }
        }
    }

    return false;
}

bool Controller::checkCollisionEnemyPlayer(int xTile, int yTile, Direction direction)
{
    if(direction == Direction::Up && this->getModel()->getPlayer()->getYTile() + 1 == yTile && this->getModel()->getPlayer()->getXTile() == xTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
        return true;
    }
    else if(direction == Direction::Down && this->getModel()->getPlayer()->getYTile() - 1 == yTile && this->getModel()->getPlayer()->getXTile() == xTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
        return true;
    }
    else if(direction == Direction::Left && this->getModel()->getPlayer()->getXTile() + 1 == xTile && this->getModel()->getPlayer()->getYTile() == yTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
        return true;
    }
    else if(direction == Direction::Right && this->getModel()->getPlayer()->getXTile() - 1 == xTile && this->getModel()->getPlayer()->getYTile() == yTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 1);
        return true;
    }

    return false;
}

void Controller::checkCollisionPlayerAmmo()
{
    if(this->getAmmoList().size() > 0)
    {
        for(int i = 0 ; i < this->getAmmoList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getYTile() == this->getAmmoList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getAmmoList()[i]->getXTile())
            {
                removeAmmo(i);
                this->model->getPlayer()->setProjectileQuantity(this->model->getPlayer()->getProjectileQuantity()+1);
            }
        }
    }
}

void Controller::checkCollisionPlayerCoffee()
{
    if(this->getCoffeeList().size() > 0)
    {
        for(int i = 0 ; i < this->getCoffeeList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getYTile() == this->getCoffeeList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getCoffeeList()[i]->getXTile() && this->model->getPlayer()->getHealthPoint() < this->model->getPlayer()->getMaxHealthPoint())
            {
                removeCoffee(i);
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint()+1);
            }
        }
    }
}

void Controller::checkCollisionPlayerHomework()
{
    if(this->getHomeworkList().size() > 0)
    {
        for(int i = 0 ; i < this->getHomeworkList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getYTile() == this->getHomeworkList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getHomeworkList()[i]->getXTile())
            {
                removeHomework(i);
                this->model->getPlayer()->setHomeworkQuantity(this->model->getPlayer()->getHomeworkQuantity()+1);
            }
        }
    }
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
                        screamSound.play();
                        randomLootOnEnemy(this->getEnemyList()[j]->getXTile(),this->getEnemyList()[j]->getYTile());
                        removeProjectile(i);
                        removeEnemy(j);
                        break;
                    }
                }
            }

        }

    }
}

void Controller::randomLootOnEnemy(int xTile, int yTile)
{
    int randomNumber = rand()%10;
    if(randomNumber == 1 || randomNumber == 2)
    {
        QVector<Ammo *>vectorAmmo = this->getAmmoList();
        vectorAmmo.append(new Ammo(xTile, yTile));
        this->setAmmoList(vectorAmmo);
    }
    else if(randomNumber == 3 || randomNumber == 4 || randomNumber == 5)
    {
        QVector<Coffee *>vectorCoffee = this->getCoffeeList();
        vectorCoffee.append(new Coffee(xTile, yTile));
        this->setCoffeeList(vectorCoffee);
    }
    else if(randomNumber == 6 || randomNumber == 7)
    {
        QVector<Homework *>vectorHomework = this->getHomeworkList();
        vectorHomework.append(new Homework(xTile, yTile));
        this->setHomeworkList(vectorHomework);
    }
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


QVector<Enemy *> Controller::getEnemyList() const
{
    return enemyList;
}

void Controller::setEnemyList(const QVector<Enemy *> &value)
{
    enemyList = value;
}

void Controller::moveEnemies()
{
    if(this->enemyList.size() > 0 )
    {
        for(int i = 0 ; i < this->enemyList.size() ; i++)
        {
            if(this->enemyList[i]->getNbMove() == 0)
            {
                int randomNumber = rand()%4;
                switch(randomNumber)
                {
                case 0:
                    this->enemyList[i]->setDirection(Direction::Up);
                    this->enemyList[i]->setTile("up");
                    break;
                case 1:
                    this->enemyList[i]->setDirection(Direction::Down);
                    this->enemyList[i]->setTile("down");
                    break;
                case 2:
                    this->enemyList[i]->setDirection(Direction::Left);
                    this->enemyList[i]->setTile("left");
                    break;
                case 3:
                    this->enemyList[i]->setDirection(Direction::Right);
                    this->enemyList[i]->setTile("right");
                    break;
                }
            }
            else if(this->enemyList[i]->getNbMove() == 1)
            {
                this->enemyList[i]->setNbMove(0);
            }

            if(getFutureTile(this->enemyList[i]->getXTile(),this->enemyList[i]->getYTile(),this->enemyList[i]->getDirection()) && !checkCollisionEnemyPlayer(this->enemyList[i]->getXTile(),this->enemyList[i]->getYTile(),this->enemyList[i]->getDirection()))
            {
                this->enemyList[i]->move();
            }
            else
            {
                this->enemyList[i]->setNbMove(0);
            }
        }
    }
}

int Controller::getTimeIterator() const
{
    return timeIterator;
}

void Controller::setTimeIterator(int value)
{
    timeIterator = value;
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

void Controller::setModel(Model *value)
{
    model = value;
}

Model *Controller::getModel() const
{
    return model;
}

QVector<Coffee *> Controller::getCoffeeList() const
{
    return coffeeList;
}

void Controller::setCoffeeList(const QVector<Coffee *> &value)
{
    coffeeList = value;
}

void Controller::removeCoffee(int vectPos)
{
    delete this->coffeeList[vectPos];
    this->coffeeList.erase(this->coffeeList.begin() + vectPos);
}

QVector<Ammo *> Controller::getAmmoList() const
{
    return ammoList;
}

void Controller::setAmmoList(const QVector<Ammo *> &value)
{
    ammoList = value;
}

void Controller::removeAmmo(int vectPos)
{
    delete this->ammoList[vectPos];
    this->ammoList.erase(this->ammoList.begin() + vectPos);
}

QVector<Homework *> Controller::getHomeworkList() const
{
    return homeworkList;
}

void Controller::setHomeworkList(const QVector<Homework *> &value)
{
    homeworkList = value;
}

void Controller::removeHomework(int vectPos)
{
    delete this->homeworkList[vectPos];
    this->homeworkList.erase(this->homeworkList.begin() + vectPos);
}
