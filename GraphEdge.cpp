#include "GraphEdge.h"
#include "WorkingField.h"
#include "Scene.h"

GraphEdge::GraphEdge(const QRect& rect, QGraphicsItem* parent):
    QGraphicsRectItem(rect, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
}

GraphEdge::~GraphEdge(){}

QRectF GraphEdge::boundingRect() const
{
    return m_boundingRect;
}


void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penBlack(Qt::black, 8);
    painter->setPen(penBlack);
    painter->drawEllipse(QRectF(10.0, 20.0, 60.0, 60.0));

}


void GraphEdge::updateBoundingRect() {
    if (m_points.empty()) return;

    qreal minX = m_points[0].x();
    qreal minY = m_points[0].y();
    qreal maxX = minX;
    qreal maxY = minY;

    for (const auto& point : m_points) {
        if (point.x() < minX) minX = point.x();
        if (point.y() < minY) minY = point.y();
        if (point.x() > maxX) maxX = point.x();
        if (point.y() > maxY) maxY = point.y();
    }

    m_boundingRect = QRectF(minX, minY, maxX - minX, maxY - minY);
}

void GraphEdge::mousePressEvent(QGraphicsSceneMouseEvent *event){
    offset = pos() - computeTopLeftGridPoint(pos());
   QGraphicsRectItem::mousePressEvent(event);
}

QPointF GraphEdge::computeTopLeftGridPoint(const QPointF& pointP){
    Scene* customScene = qobject_cast<Scene*> (scene());
    int gridSize = customScene->getGridSize();
    qreal xV = float(pointP.x()/gridSize)*gridSize;
    qreal yV = float(pointP.y()/gridSize)*gridSize;
    return QPointF(xV, yV);
}

QVariant GraphEdge::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton && qobject_cast<Scene*> (scene())){
                QPointF closestPoint = computeTopLeftGridPoint(newPos);
                return  closestPoint+=offset;
            }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}
