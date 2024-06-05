//main.cpp
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ball.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a new scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Set the scene's boundaries
    scene->setSceneRect(0, 0, 1280, 720);

    // Load and scale the background image
    QPixmap bgPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bgGame.png");
    QPixmap scaledBgPixmap = bgPixmap.scaled(scene->sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);

    // Add background image
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(scaledBgPixmap);
    background->setPos(0, 0);
    scene->addItem(background);


    // Create a new Ball item
    Ball *ball = new Ball(0, 0, 50, 50);
    ball->setPos(scene->width() / 2 - ball->pixmap().width() / 2, scene->height() / 2 - ball->pixmap().height() / 2);

    // Add the Ball item to the scene
    scene->addItem(ball);

    // Create a view to visualize the scene
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable horizontal scrollbar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Disable vertical scrollbar
    view->setSceneRect(0, 0, 1280, 720); // Match scene rect to the scene's boundaries

    // Start the game loop
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(30);

    // Show the view
    view->show();

    return a.exec();
}
