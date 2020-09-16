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
    updateGame();
    this->view->show();
}

void Controller::updateGame()
{
    this->view->resetView();
    this->view->displayMap(this->getModel()->getPlayer());
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
    if(key == "up" || key == "down" || key == "left" || key == "right"){
        this->model->getPlayer()->setTile(key);
        this->model->getPlayer()->move(key);

    }
}

