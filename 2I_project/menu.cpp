#include "menu.h"
#include "ui_menu.h"
#include "controller.h"
#include <QFontDatabase>
#include <QBrush>
extern Controller *pointerCtrl;

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/images/icon.ico"));
    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/title.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont titleFont(family);
    titleFont.setPointSize(40);
    this->titreLabel = new QLabel(this);
    this->titreLabel->setText("PiouPiou Game");
    this->titreLabel->setFont(titleFont);
    this->titreLabel->adjustSize();
    this->titreLabel->setGeometry(0,0,450,150);
    this->titreLabel->setAlignment(Qt::AlignCenter);
    this->titreLabel->setStyleSheet("QLabel {color : #FFDAB9; }");
    titleFont.setPointSize(20);
    ui->playButton->setFont(titleFont);
    ui->rulesButton->setFont(titleFont);
    ui->quitButton->setFont(titleFont);
    QPixmap bkgnd(":/images/images/menu_background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_playButton_clicked()
{
    pointerCtrl->startGame();

}

void Menu::on_rulesButton_clicked()
{
    pointerCtrl->showRules();
}

void Menu::on_quitButton_clicked()
{
    qApp->exit();
}
