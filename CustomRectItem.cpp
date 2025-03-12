#include "CustomRectItem.h"

CustomRectItem::CustomRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    :QGraphicsEllipseItem(x, y, w, h, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
                QGraphicsItem::ItemIsMovable |
                QGraphicsItem::ItemSendsGeometryChanges);
}

void CustomRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    offset = pos() - computeTopLeftGridPoint(pos());
    QGraphicsEllipseItem::mousePressEvent(event);
    update();
}

QVariant CustomRectItem::itemChange(GraphicsItemChange change,
const QVariant &value)
{
    if (change == ItemPositionChange) {
        QPointF newPos = value.toPointF();
        updateLinePosition();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
            qobject_cast<Scene*> (scene())){
                QPointF closestPoint = computeTopLeftGridPoint(newPos);
                return closestPoint+=offset;
            }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

void CustomRectItem::setLineItem(CustomLineItem *item, bool isStart){
    QPair<CustomLineItem*, bool> pair;
    pair.first = item;
    pair.second = isStart;
    lines.push_back(pair);
}

void CustomRectItem::updateLinePosition(){
    QPointF center = mapToScene(rect().center());

    for (const auto& lineInfo : lines) {
        QGraphicsLineItem* lineItem = lineInfo.first;
        bool isStartPoint = lineInfo.second;

        QLineF line = lineItem->line();
        if (isStartPoint) {
            line.setP1(center); // Обновляем начальную точку линии
        } else {
            line.setP2(center); // Обновляем конечную точку линии
        }
        lineItem->setLine(line);
    }
}

QPointF CustomRectItem::computeTopLeftGridPoint(const QPointF& pointP){
    Scene* customScene = qobject_cast<Scene*> (scene());
    int gridSize = customScene->getGridSize();
    qreal xV = floor(pointP.x()/gridSize)*gridSize;
    qreal yV = floor(pointP.y()/gridSize)*gridSize;
    return QPointF(xV, yV);
}

QRectF CustomRectItem::boundingRect() const
{
    return m_boundingRect;
}

void CustomRectItem::updateBoundingRect() {
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
