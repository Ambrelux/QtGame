#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QImage>
namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_playButton_clicked();

    void on_rulesButton_clicked();

private:
    Ui::Menu *ui;
    QLabel *titreLabel;
};

#endif // MENU_H
