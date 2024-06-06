#include "Ball.h"
#include <iostream>

Ball::Ball(qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsPixmapItem(), ballWidth(width), ballHeight(height), currentFrame(0), frameInterval(100), frameTimer(0)
    , velocityY(0), gravity(0.5), bounceFactor(0.7), shadow(nullptr) // Initialize shadow to nullptr
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
    // Get the boundaries of the scene
    qreal sceneBottom = scene()->sceneRect().bottom() - 230;

    if (!step) return;

    // Delayed shadow initialization
    if (!shadow) {
        shadow = new Shadow(x() + ballWidth / 4, sceneBottom - ballHeight / 8, ballWidth / 2, ballHeight / 8, scene());
        std::cout<<"Shadow spawned!";
    }

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

    // Check for collision with the bottom of the scene
    if (newY + pixmap().height() > sceneBottom) {
        newY = sceneBottom - pixmap().height(); // Place the ball on the ground
        velocityY = -velocityY * bounceFactor;  // Reverse and reduce velocity
    }

    // Move the ball
    setPos(x(), newY);
    shadow->updateShadow(newY, pixmap().height()); // Update shadow

    // Stop the ball if it's moving very slowly
    if (abs(velocityY) < 1 && newY + pixmap().height() >= sceneBottom) {
        velocityY = 0;
    }
}
