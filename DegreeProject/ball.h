#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QObject>

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    Ball(qreal x, qreal y, qreal width, qreal height);

public slots:
    void moveBall();

private:
    qreal dx;
    qreal dy;
    QTimer *timer;
};

#endif // BALL_H
