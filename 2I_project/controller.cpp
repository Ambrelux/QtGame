#include "controller.h"

Controller::Controller(MainWindow *view, Model *model, Menu *menu, Rules *rules)
{
    this->view = view;
    this->model = model;
    this->menu = menu;
    this->rules = rules;

    srand((unsigned) time(0));
    this->timer =  new QTimer();
    timer->connect(timer,SIGNAL(timeout()), this, SLOT(updateGame()));
    this->setTimeIterator(0);

    this->whistleSound.setMedia(QUrl("qrc:/sounds/sounds/whistle.wav"));
    this->screamSound.setMedia(QUrl("qrc:/sounds/sounds/scream.wav"));
    this->drinkSound.setMedia(QUrl("qrc:/sounds/sounds/drink.mp3"));
    this->bgMusic.setMedia(QUrl("qrc:/sounds/sounds/bgMusic.mp3"));
}

void Controller::startGame(){
    this->bgMusic.stop();
    this->menu->close();

    state = 0;
    this->view->displayEndGame("","FFFFFF");
    this->mapInitialization();
    updateGame();
    this->view->show();
}

void Controller::updateGame()
{
    this->setTimeIterator(this->getTimeIterator() + 1);
    if(this->getTimeIterator() % 10 == 0)
    {
        moveEnemies();
    }
    this->moveProjectiles();
    this->checkCollisionProjectile();
    this->checkCollisionPlayerAmmo();
    this->checkCollisionPlayerCoffee();
    this->checkCollisionPlayerHomework();

    this->view->resetView();
    this->view->displayMap(this->getModel()->getPlayer(),this->getModel()->getMap());
    this->view->displayPlayer(this->getModel()->getPlayer());
    this->view->displayEnemy(this->getEnemyList());
    this->view->displayProjectile(this->getProjectileList());
    this->view->displayAmmo(this->getAmmoList());
    this->view->displayCoffee(this->getCoffeeList());
    this->view->displayHomework(this->getHomeworkList());
    this->view->displayUI(this->getModel()->getPlayer());


    if(this->getModel()->getPlayer()->getHomeworkQuantity() >= 10 && this->getModel()->getBoss()->getHealthPoint() > 0)
    {
        this->view->displayBoss(this->getModel()->getBoss());
        if(this->getTimeIterator() % 10 == 0)
        {
            this->createProjectile(this->getModel()->getBoss()->getXTile(),this->getModel()->getBoss()->getYTile(),this->getModel()->getBoss()->getDirection());
        }
    }

    if(this->getModel()->getPlayer()->getHealthPoint()>0)
    {
        timer->start(10);
    }

    this->endGame();
}

/*!
    Set up map's elements (walkable tiles, enemies and items) by reading a textfile.
*/
void Controller::mapInitialization()
{
    QFile file(this->getModel()->getMap()->getFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QVector<QString> _mapMatrix;
    QString line;
    QVector<Enemy *> vectEnemy;
    QVector<Homework *> vectHomework;

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

/*!
    check if the unit can move on a tile. Return true if it is possible else false.
*/
bool Controller::checkTile(int xTile, int yTile, Direction direction)
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

/*!
    function called when user press A key. If there is an enemy on the next tile he will lose health.
*/
void Controller::playerAttack()
{
    whistleSound.play();
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

    if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() - 1 == this->getModel()->getBoss()->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getModel()->getBoss()->getXTile())
    {
        this->getModel()->getBoss()->setHealthPoint(this->getModel()->getBoss()->getHealthPoint()-2);
    }
    else if(this->getModel()->getPlayer()->getDirection() == Direction::Down && this->getModel()->getPlayer()->getYTile() + 1 == this->getModel()->getBoss()->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getModel()->getBoss()->getXTile())
    {
        this->getModel()->getBoss()->setHealthPoint(this->getModel()->getBoss()->getHealthPoint()-2);
    }
    else if(this->getModel()->getPlayer()->getDirection() == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getModel()->getBoss()->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getModel()->getBoss()->getYTile())
    {
        this->getModel()->getBoss()->setHealthPoint(this->getModel()->getBoss()->getHealthPoint()-2);
    }
    else if(this->getModel()->getPlayer()->getDirection() == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getModel()->getBoss()->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getModel()->getBoss()->getYTile())
    {
        this->getModel()->getBoss()->setHealthPoint(this->getModel()->getBoss()->getHealthPoint()-2);
    }
}

/*!
    Returns true if the player will collide with an enemy (he also lose healthpoint), else false.
*/
bool Controller::checkCollisionPlayerEnemy()
{
    if(this->getEnemyList().size() > 0)
    {
        for(int i = 0 ; i < this->getEnemyList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() - 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Down && this->getModel()->getPlayer()->getYTile() + 1 == this->getEnemyList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getEnemyList()[i]->getXTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
                return true;
            }
            else if(this->getModel()->getPlayer()->getDirection() == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getEnemyList()[i]->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getEnemyList()[i]->getYTile())
            {
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
                return true;
            }
        }
    }

    return false;
}

/*!
    Returns true if the player will collide with the boss (he also lose healthpoint), else false.
*/
bool Controller::checkCollisionPlayerBoss()
{
    if(this->getModel()->getPlayer()->getDirection() == Direction::Up && this->getModel()->getPlayer()->getYTile() + 1 == this->getModel()->getBoss()->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getModel()->getBoss()->getXTile())
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(this->getModel()->getPlayer()->getDirection()  == Direction::Down && this->getModel()->getPlayer()->getYTile() - 1 == this->getModel()->getBoss()->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getModel()->getBoss()->getXTile())
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(this->getModel()->getPlayer()->getDirection()  == Direction::Left && this->getModel()->getPlayer()->getXTile() - 1 == this->getModel()->getBoss()->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getModel()->getBoss()->getYTile())
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(this->getModel()->getPlayer()->getDirection()  == Direction::Right && this->getModel()->getPlayer()->getXTile() + 1 == this->getModel()->getBoss()->getXTile() && this->getModel()->getPlayer()->getYTile() == this->getModel()->getBoss()->getYTile())
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }

    return false;
}

/*!
    Returns true if the enemy will collide with the player (player also lose healthpoint), else false.
*/
bool Controller::checkCollisionEnemyPlayer(int xTile, int yTile, Direction direction)
{
    if(direction == Direction::Up && this->getModel()->getPlayer()->getYTile() + 1 == yTile && this->getModel()->getPlayer()->getXTile() == xTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(direction == Direction::Down && this->getModel()->getPlayer()->getYTile() - 1 == yTile && this->getModel()->getPlayer()->getXTile() == xTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(direction == Direction::Left && this->getModel()->getPlayer()->getXTile() + 1 == xTile && this->getModel()->getPlayer()->getYTile() == yTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }
    else if(direction == Direction::Right && this->getModel()->getPlayer()->getXTile() - 1 == xTile && this->getModel()->getPlayer()->getYTile() == yTile)
    {
        this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint() - 0.5);
        return true;
    }

    return false;
}

/*!
    Returns true if the enemy will collide with another enemy, else false.
*/
bool Controller::checkCollisionEnemyEnemy(int xTile, int yTile, Direction direction)
{
    if(this->getEnemyList().size() > 0)
    {
        for( int i = 0 ; i < this->getEnemyList().size() ; i++)
        {
            if(direction == Direction::Up && this->getEnemyList()[i]->getYTile() == yTile + 1 && this->getEnemyList()[i]->getXTile() == xTile)
            {
                return true;
            }
            else if(direction == Direction::Down && this->getEnemyList()[i]->getYTile() == yTile - 1 && this->getEnemyList()[i]->getXTile() == xTile)
            {
                return true;
            }
            else if(direction == Direction::Left && this->getEnemyList()[i]->getXTile() == xTile + 1 && this->getEnemyList()[i]->getYTile() == yTile)
            {
                return true;
            }
            else if(direction == Direction::Right && this->getEnemyList()[i]->getXTile() == xTile - 1 && this->getEnemyList()[i]->getYTile() == yTile)
            {
                return true;
            }

            return false;
        }
    }

    return false;
}

/*!
    Returns true if the enemy will collide with the boss, else false.
*/
bool Controller::checkCollisionEnemyBoss(int xTile, int yTile, Direction direction)
{
    if(direction == Direction::Up && this->getModel()->getBoss()->getYTile() + 1 == yTile && this->getModel()->getBoss()->getXTile() == xTile)
    {
        return true;
    }
    else if(direction == Direction::Down && this->getModel()->getBoss()->getYTile() - 1 == yTile && this->getModel()->getBoss()->getXTile() == xTile)
    {
        return true;
    }
    else if(direction == Direction::Left && this->getModel()->getBoss()->getXTile() + 1 == xTile && this->getModel()->getBoss()->getYTile() == yTile)
    {
        return true;
    }
    else if(direction == Direction::Right && this->getModel()->getBoss()->getXTile() - 1 == xTile && this->getModel()->getBoss()->getYTile() == yTile)
    {
        return true;
    }

    return false;
}

/*!
    Check if the player is on the same tile as an ammo, if it is the ammo is removed and projectile quantity is increased.
*/
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

/*!
    Check if the player is on the same tile as a coffee, if it is and player health is not full, the coffee is removed and health point is increased.
*/
void Controller::checkCollisionPlayerCoffee()
{
    if(this->getCoffeeList().size() > 0)
    {
        for(int i = 0 ; i < this->getCoffeeList().size() ; i++)
        {
            if(this->getModel()->getPlayer()->getYTile() == this->getCoffeeList()[i]->getYTile() && this->getModel()->getPlayer()->getXTile() == this->getCoffeeList()[i]->getXTile() && this->model->getPlayer()->getHealthPoint() < this->model->getPlayer()->getMaxHealthPoint())
            {
                drinkSound.play();
                removeCoffee(i);
                this->model->getPlayer()->setHealthPoint(this->model->getPlayer()->getHealthPoint()+1);
            }
        }
    }
}

/*!
    Check if the player is on the same tile as a homework, if it is the homework is removed and homework count is increased.
*/
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

/*!
    Check if a projectile collides with a unit. If it is the unit takes damages and the projectile is removed.
*/
void Controller::checkCollisionProjectile()
{
    // check collisions projectiles enemies
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
                        this->screamSound.play();
                        this->randomLootOnEnemy(this->getEnemyList()[j]->getXTile(),this->getEnemyList()[j]->getYTile());
                        this->removeProjectile(i);
                        this->removeEnemy(j);
                        break;
                    }
                }
            }
        }

        // check collisions projectiles boss
        for(int i = 0 ; i < this->getProjectileList().size() ; i++)
        {
            if(this->getProjectileList()[i]->getXTile() == this->getModel()->getBoss()->getXTile() && this->getProjectileList()[i]->getYTile() == this->getModel()->getBoss()->getYTile())
            {
                this->getModel()->getBoss()->setHealthPoint(this->getModel()->getBoss()->getHealthPoint() - 5);
                this->removeProjectile(i);
                break;
            }
        }

        // check collision projectiles player
        for(int i = 0 ; i < this->getProjectileList().size() ; i++)
        {
            if(this->getProjectileList()[i]->getXTile() == this->getModel()->getPlayer()->getXTile() && this->getProjectileList()[i]->getYTile() == this->getModel()->getPlayer()->getYTile())
            {
                this->getModel()->getPlayer()->setHealthPoint(this->getModel()->getPlayer()->getHealthPoint()-1);
                this->removeProjectile(i);
                break;
            }
        }

    }
}

/*!
    Function called when player press space bar or when the boss spawn. It creates a new projectile.
*/
void Controller::createProjectile(int xTile, int yTile, Direction direction)
{
    QVector<Projectile *> vect = this->getProjectileList();
    vect.push_back(new Projectile(xTile,yTile,direction));
    this->setProjectileList(vect);
}

/*!
    Move each projectile if it is possible. (check max distance and walkable tile)
*/
void Controller::moveProjectiles()
{
    if(this->getProjectileList().size() > 0)
    {
        for(int i = 0 ; i < this->getProjectileList().size() ; i++)
        {
            if(checkTile(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getDirection()) && checkMaxDistance(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getInitialXTile(),this->getProjectileList()[i]->getInitialYTile(),this->getProjectileList()[i]->getMaxDistance()))
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
            else if (!checkTile(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getDirection()) || !checkMaxDistance(this->getProjectileList()[i]->getXTile(),this->getProjectileList()[i]->getYTile(),this->getProjectileList()[i]->getInitialXTile(),this->getProjectileList()[i]->getInitialYTile(),this->getProjectileList()[i]->getMaxDistance()))
            {
                removeProjectile(i);
            }
        }
    }
}



/*!
    Function called when enemies died. There is 20% chance to loot ammo or homework and 30% chance to loot coffee.
*/
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

/*!
    Function called to move projectile. Returns true if it travelled more than max distance, else false.
*/
bool Controller::checkMaxDistance(int xTile, int yTile, int xInitialTile, int yInitialTile, int maxDistance)
{
    int diffX = xTile - xInitialTile;
    int diffY = yTile - yInitialTile;

    if(diffX < maxDistance && diffX > - maxDistance && diffY < maxDistance && diffY > - maxDistance)
    {
        return true;
    }

    return false;
}

/*!
    Function called to move enemies randomly.
*/
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

            if(checkTile(this->enemyList[i]->getXTile(),this->enemyList[i]->getYTile(),this->enemyList[i]->getDirection()) && !checkCollisionEnemyPlayer(this->enemyList[i]->getXTile(),this->enemyList[i]->getYTile(),this->enemyList[i]->getDirection()) && !checkCollisionEnemyEnemy(this->enemyList[i]->getXTile(),this->enemyList[i]->getYTile(),this->enemyList[i]->getDirection()))
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

/*
    GETTERS, SETTERS AND DELETERS.
*/

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

int Controller::getTimeIterator() const
{
    return timeIterator;
}

void Controller::setTimeIterator(int value)
{
    timeIterator = value;
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

/*!
    Function called to show end screen for defeat or victory.
*/
void Controller::endGame()
{
    if(state == 1){
        this->showMenu();
    }

    if(this->getModel()->getPlayer()->getHealthPoint()<0.5)
    {
        this->view->displayEndGame("Defeat","FF0000");
        state=1;
    }
    else if(this->getModel()->getBoss()->getHealthPoint() < 0.5)
    {
        this->view->displayEndGame("Victory","FFD700");
        state = 1;
    }
}

/*!
    Function to stop the program for i seconds
*/
void Controller::delay(int i)
{
    QTime dieTime= QTime::currentTime().addSecs(i);
    while (QTime::currentTime() < dieTime)
    {
    }
}

/*!
    Function called when the game ended, it clears each list. (ammo, coffee, homework, projectile, enemy)
*/
void Controller::resetList()
{
    for(int i = 0 ; i < this->getEnemyList().size() ; i++)
    {
        this->removeEnemy(i);
    }
    for(int i = 0 ; i < this->getProjectileList().size() ; i++)
    {
        this->removeProjectile(i);
    }
    for(int i = 0 ; i < this->getCoffeeList().size() ; i++)
    {
        this->removeCoffee(i);
    }
    for(int i = 0 ; i < this->getHomeworkList().size() ; i++)
    {
        this->removeHomework(i);
    }
    for(int i = 0 ; i < this->getAmmoList().size() ; i++)
    {
        this->removeAmmo(i);
    }
}

/*!
    Show rules' window.
*/
void Controller::showRules()
{
    this->rules->show();
}

/*!
    Show menu's window.
*/
void Controller::showMenu()
{
    if(state==1){
        delay(2);
    }
    this->timer->stop();
    this->getModel()->resetModel();
    this->resetList();
    this->view->close();
    this->menu->show();
    this->bgMusic.play();
}

/*!
    Function called when user press key.
*/
void Controller::keyPressed(QString key)
{
    if(key == "up")
    {
        this->getModel()->getPlayer()->setTile(key);
        this->getModel()->getPlayer()->setDirection(Direction::Up);
        if(checkTile(this->getModel()->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->getModel()->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy() && !checkCollisionPlayerBoss())
        {
            this->getModel()->getPlayer()->move();
        }

    }
    else if(key == "down")
    {
        this->getModel()->getPlayer()->setTile(key);
        this->getModel()->getPlayer()->setDirection(Direction::Down);
        if(checkTile(this->getModel()->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->getModel()->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy() && !checkCollisionPlayerBoss())
        {
            this->getModel()->getPlayer()->move();
        }
    }
    else if(key == "left")
    {
        this->getModel()->getPlayer()->setTile(key);
        this->getModel()->getPlayer()->setDirection(Direction::Left);
        if(checkTile(this->getModel()->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->getModel()->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy() && !checkCollisionPlayerBoss())
        {
            this->getModel()->getPlayer()->move();
        }
    }
    else if(key == "right")
    {
        this->getModel()->getPlayer()->setTile(key);
        this->getModel()->getPlayer()->setDirection(Direction::Right);
        if(checkTile(this->getModel()->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->getModel()->getPlayer()->getDirection()) && !checkCollisionPlayerEnemy() && !checkCollisionPlayerBoss())
        {
            this->getModel()->getPlayer()->move();
        }
    }
    else if(key == "space")
    {
        if(this->getModel()->getPlayer()->getProjectileQuantity() > 0)
        {
            this->getModel()->getPlayer()->setProjectileQuantity(this->getModel()->getPlayer()->getProjectileQuantity() - 1);
            this->createProjectile(this->getModel()->getPlayer()->getXTile(),this->getModel()->getPlayer()->getYTile(),this->getModel()->getPlayer()->getDirection());
        }
    }
    else if(key == "a")
    {
        playerAttack();
    }
    else if(key == "r")
    {
        this->showRules();
    }
    else if(key == "m")
    {
        this->showMenu();
    }
}
