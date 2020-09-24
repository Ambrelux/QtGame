#include <QApplication>
#include "model.h"
#include "mainwindow.h"
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
    pointerCtrl->showMenu();

    //controller.startGame();
    return a.exec();
}
