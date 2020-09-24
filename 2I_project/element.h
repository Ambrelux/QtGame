#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

enum class Direction {
    Up,Down,Left,Right

};

class Element: public QObject{

    Q_OBJECT
public:
    Element();
    QPixmap getTile();
    void setTile(QString _tile);


    int getXCoord() const;
    void setXCoord(int value);

    int getYCoord() const;
    void setYCoord(int value);

    int getXTile() const;
    void setXTile(int value);

    int getYTile() const;
    void setYTile(int value);


    QString getTilePath() const;
    void setTilePath(const QString &value);
    Direction getDirection() const;
    void setDirection(const Direction &value);

private:
    QPixmap tile;
    int xCoord;
    int yCoord;
    int xTile;
    int yTile;
    QString tilePath;
    Direction direction;

};

#endif // ELEMENT_H
