#include "Scene.h"

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent), gridSize(20)
{
    Q_ASSERT(gridSize > 0);
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += gridSize){
        for (qreal y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->setPen(QPen(QColor(0, 0, 0)));;
    painter->drawPoints(points.data(), points.size());
}
