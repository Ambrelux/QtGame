#include <QApplication>
#include "model.h"
#include "view.h"
#include "controller.h"

Controller *pointerCtrl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    View view;
    Controller controller(&view,&model);
    pointerCtrl = &controller;
    controller.startGame();
    return a.exec();
}
