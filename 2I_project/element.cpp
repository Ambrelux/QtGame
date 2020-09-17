#include "element.h"
#include <QGraphicsScene>
#include <QDebug>
Element::Element(): QObject(){


}

QPixmap Element::getTile()
{
    return this->tile;
}

void Element::setTile(QString _tile)
{
    this->tile=QPixmap(":/images/images/player_"+_tile+".png");
}

int Element::getXCoord() const
{
    return this->xCoord;
}

void Element::setXCoord(int value)
{
    this->xCoord = value;
}

int Element::getYCoord() const
{
    return this->yCoord;
}

void Element::setYCoord(int value)
{
    this->yCoord = value;
}

int Element::getXTile() const
{
    return xTile;
}

void Element::setXTile(int value)
{
    xTile = value;
}

int Element::getYTile() const
{
    return yTile;
}

void Element::setYTile(int value)
{
    yTile = value;
}

