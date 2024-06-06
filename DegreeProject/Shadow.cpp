#include "Shadow.h"
#include <QGraphicsScene>

Shadow::Shadow(qreal x, qreal y, qreal width, qreal height, QGraphicsScene* scene)
    : QObject(), QGraphicsEllipseItem(x, y, width, height), scene(scene)
{
    setBrush(QBrush(Qt::black, Qt::SolidPattern));
    setOpacity(0.5); // Semi-transparent shadow
    scene->addItem(this); // Add the shadow to the scene
}

void Shadow::updateShadow(qreal ballY, qreal ballHeight) {
    qreal shadowY = scene->sceneRect().bottom() - rect().height() / 2 - 230;
    setPos(x(), shadowY);

    qreal distance = (scene->sceneRect().bottom() - 230) - (ballY + ballHeight);
    qreal scale = 1.0 - (distance / scene->sceneRect().height());
    scale = qMax(0.5, scale); // Ensure shadow doesn't become too small

    QTransform transform;
    transform.scale(scale, 1); // Scale only horizontally
    setTransform(transform);
    setOpacity(0.5 * scale); // More distance, less opacity
}
