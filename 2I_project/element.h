#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

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

private:
    QPixmap tile;
    int xCoord;
    int yCoord;
    int xTile;
    int yTile;

};

#endif // ELEMENT_H
