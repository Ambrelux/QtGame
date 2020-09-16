#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QKeyEvent>

#include "player.h"
#include "controller.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    //~View();

    //variables
    QGraphicsScene * scene;

    //function
    void keyPressEvent(QKeyEvent *event);
    void displayMap(Player *player);
    void displayPlayer(Player *player);
    void resetView();

};

#endif // VIEW_H
