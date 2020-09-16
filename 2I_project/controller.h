#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QKeyEvent>

#include "model.h"
#include "view.h"

class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(class View *view, class Model *model);
    //~Controller();

    void startGame();
    void setModel(Model *value);
    Model *getModel() const;
    void keyPressed(QString key);

public slots:
    void updateGame();

private:
    Model *model;
    View *view;
    QTimer *timer;
};

#endif // CONTROLLER_H
