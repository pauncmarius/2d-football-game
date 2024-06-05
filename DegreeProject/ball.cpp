#include "ball.h"

Ball::Ball(qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsPixmapItem(), ballWidth(width), ballHeight(height), currentFrame(0)
    ,velocityY(0), gravity(0.5), bounceFactor(0.7)
{
    // Load the four frames of the ball animation
    QPixmap originalPixmap("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/balls.png");
    // Calculate the width of a single frame
    int frameWidth = originalPixmap.width() / 2;
    int frameHeight = originalPixmap.height() / 2;

    // Extract each frame from the original pixmap
    frames.push_back(originalPixmap.copy(0, 0, frameWidth, frameHeight).scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(originalPixmap.copy(frameWidth, 0, frameWidth, frameHeight).scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(originalPixmap.copy(0, frameHeight, frameWidth, frameHeight).scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));
    frames.push_back(originalPixmap.copy(frameWidth, frameHeight, frameWidth, frameHeight).scaled(ballWidth, ballHeight, Qt::KeepAspectRatio));

    setPixmap(frames[currentFrame]);
    setPos(x, y);
}

void Ball::advance(int step)
{
    if (!step) return;

    // Update the current frame for the animation
    currentFrame = (currentFrame + 1) % frames.size();
    setPixmap(frames[currentFrame]);

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
