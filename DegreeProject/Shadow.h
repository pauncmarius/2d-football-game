#ifndef SHADOW_H
#define SHADOW_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsScene>

class Shadow : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    Shadow(qreal x, qreal y, qreal width, qreal height, QGraphicsScene* scene);

public slots:
    void updateShadow(qreal ballY, qreal ballHeight);

private:
    QGraphicsScene* scene;
};

#endif // SHADOW_H
