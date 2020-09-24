#include "map.h"
#include <QDebug>

Map::Map()
{

}

QString Map::getFileName() const
{
    return fileName;
}

void Map::setFileName(const QString &value)
{
    fileName = value;
}

QString Map::getMapImagePath() const
{
    return mapImagePath;
}

void Map::setMapImagePath(const QString &value)
{
    mapImagePath = value;
}

QVector<QString> Map::getMapMatrix() const
{
    return mapMatrix;
}

void Map::setMapMatrix(const QVector<QString> &value)
{
    mapMatrix = value;
}
