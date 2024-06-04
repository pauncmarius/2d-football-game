#include "game.h"
#include "ui_game.h"
#include <QPixmap>
#include <QVBoxLayout>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
    , backgroundLabel(new QLabel(this))
{
    ui->setupUi(this);

    //bg load
    QPixmap backgroundPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg.png");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true); //auto scaling
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(backgroundLabel);
    this->setLayout(mainLayout);

    //hd size for window
    this->setFixedSize(1280, 720);

}

Game::~Game()
{
    delete ui;
}
