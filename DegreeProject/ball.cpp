#include "ball.h"

Ball::Ball(qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsPixmapItem(), ballWidth(width), ballHeight(height), currentFrame(0)
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
}
