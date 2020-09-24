#ifndef MAP_H
#define MAP_H
#include <QString>
#include <QVector>
#include <QImage>
#include <QFile>
#include <QTextStream>

class Map
{
public:
    Map();

    QString getFileName() const;
    void setFileName(const QString &value);

    QString getMapImagePath() const;
    void setMapImagePath(const QString &value);

    QVector<QString> getMapMatrix() const;
    void setMapMatrix(const QVector<QString> &value);

private:
    QString fileName=":/maps/maps/map_matrix.txt";
    QString mapImagePath=":/images/images/map.png";
    QVector<QString> mapMatrix;




};

#endif // MAP_H
