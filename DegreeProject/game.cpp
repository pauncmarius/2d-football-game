#include "game.h"
#include "ui_game.h"
#include <iostream>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    //hd size for window
    this->setFixedSize(1280, 720);

}

Game::~Game()
{
    delete ui;
}
