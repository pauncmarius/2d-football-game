#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>
#include <vector>

class Ball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Ball(qreal x, qreal y, qreal width, qreal height);

protected:
    void advance(int step) override;

private:

    qreal ballWidth;
    qreal ballHeight;

    int currentFrame;
    std::vector<QPixmap> frames;

    qreal velocityY;          // Vertical velocity
    const qreal gravity;      // Acceleration due to gravity
    const qreal bounceFactor; // Energy loss factor on bounce
};

#endif // BALL_H
