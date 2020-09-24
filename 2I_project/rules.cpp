#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/images/images/menu_background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

Rules::~Rules()
{
    delete ui;
}
