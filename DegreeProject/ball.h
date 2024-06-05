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
    qreal dx;
    qreal dy;
    qreal ballWidth;
    qreal ballHeight;
    qreal speedMultiplier;
    int currentFrame;
    std::vector<QPixmap> frames;
};

#endif // BALL_H
