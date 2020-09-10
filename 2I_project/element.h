#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
class Element: public QObject,public QGraphicsPixmapItem{

    Q_OBJECT
public:
    Element(QGraphicsItem * parent=0);
};

#endif // ELEMENT_H
