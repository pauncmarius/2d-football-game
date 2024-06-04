#include "ball.h"

Ball::Ball(qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsEllipseItem(), dx(2), dy(2)
{
    setRect(x, y, width, height);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::moveBall);
    timer->start(16); // Move the ball every 30 milliseconds
}

void Ball::moveBall()
{
    qreal newX = x() + dx;
    qreal newY = y() + dy;

    // Get the boundaries of the scene
    qreal sceneLeft = scene()->sceneRect().left();
    qreal sceneRight = scene()->sceneRect().right();
    qreal sceneTop = scene()->sceneRect().top();
    qreal sceneBottom = scene()->sceneRect().bottom();

    // Check for collision with the scene boundaries
    if (newX < sceneLeft || newX + rect().width() > sceneRight) {
        dx = -dx; // Reverse horizontal direction
    }
    if (newY < sceneTop || newY + rect().height() > sceneBottom) {
        dy = -dy; // Reverse vertical direction
    }

    // Move the ball
    setPos(x() + dx, y() + dy);
}
