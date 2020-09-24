#include <QApplication>
#include "model.h"
#include "mainWindow.h"
#include "controller.h"
#include "menu.h"
#include "rules.h"
Controller *pointerCtrl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow view;
    Menu menu;
    Rules rules;
    Controller controller(&view,&model,&menu,&rules);
    pointerCtrl = &controller;
    menu.show();

    //controller.startGame();
    return a.exec();
}
