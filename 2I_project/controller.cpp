#include "controller.h"
#include <QtDebug>
Controller::Controller(View *view, Model *model)
{
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
    timer->start(10);
}

void Controller::setModel(Model *value)
{
    model = value;
}

Model *Controller::getModel() const
{
    return model;
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
    if(futureTile == 1)
    {
        return true;
    }
    else if(futureTile == 0)
    {
        return false;
    }

    return false;
}

