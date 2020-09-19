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
    this->tile=QPixmap(this->getTilePath()+ _tile+".png");
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

QString Element::getTilePath() const
{
    return tilePath;
}

void Element::setTilePath(const QString &value)
{
    tilePath = value;
}

Direction Element::getDirection() const
{
    return direction;
}

void Element::setDirection(const Direction &value)
{
    direction = value;
}
