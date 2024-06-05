#include "ball.h"

Ball::Ball(qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsPixmapItem(), ballWidth(width), ballHeight(height), currentFrame(0), frameInterval(100), frameTimer(0)
    ,velocityY(0), gravity(0.5), bounceFactor(0.7)
{
    // Load the four individual frames of the ball animation
    frames.push_back(QPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png").scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(QPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball2.png").scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(QPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball3.png").scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(QPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball4.png").scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));

    setPixmap(frames[currentFrame]);
    setPos(x, y);
}

void Ball::advance(int step)
{
    if (!step) return;

    // Check if the ball has stopped
    if (velocityY != 0) {
        // Update the frame based on the frame interval
        frameTimer += 30;
        if (frameTimer >= frameInterval) {
            frameTimer = 0;
            currentFrame = (currentFrame + 1) % frames.size();
            setPixmap(frames[currentFrame]);
        }
    }

    // Apply gravity
    velocityY += gravity;

    // Move the ball vertically
    qreal newY = y() + velocityY;

    // Get the boundaries of the scene
    qreal sceneBottom = scene()->sceneRect().bottom();

    // Check for collision with the bottom of the scene
    if (newY + pixmap().height() > sceneBottom) {
        newY = sceneBottom - pixmap().height(); // Place the ball on the ground
        velocityY = -velocityY * bounceFactor;  // Reverse and reduce velocity
    }

    // Move the ball
    setPos(x(), newY);

    // Stop the ball if it's moving very slowly
    if (abs(velocityY) < 1 && newY + pixmap().height() >= sceneBottom) {
        velocityY = 0;
    }
}
