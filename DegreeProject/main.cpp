#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ball.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a new scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Set the scene's boundaries
    scene->setSceneRect(0, 0, 1280, 720);

    // Create a new Ball item
    Ball *ball = new Ball(0, 0, 100, 100);

    // Add the Ball item to the scene
    scene->addItem(ball);

    // Create a view to visualize the scene
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable horizontal scrollbar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Disable vertical scrollbar
    view->setSceneRect(0, 0, 1280, 720); // Match scene rect to the scene's boundaries

    // Show the view
    view->show();

    return a.exec();
}
