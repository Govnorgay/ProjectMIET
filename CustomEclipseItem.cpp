#include "CustomEclipseItem.h"

CustomEclipseItem::CustomEclipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    :QGraphicsEllipseItem(x, y, w, h, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
                QGraphicsItem::ItemIsMovable |
                QGraphicsItem::ItemSendsGeometryChanges);

    m_boundingRect = QRectF(x, y, w, h);
}

void CustomEclipseItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    offset = pos() - computeTopLeftGridPoint(pos());
    QGraphicsEllipseItem::mousePressEvent(event);
}

QVariant CustomEclipseItem::itemChange(GraphicsItemChange change,
const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        updateLinePosition();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
            qobject_cast<Scene*> (scene())){
                QPointF closestPoint = computeTopLeftGridPoint(newPos);
                return closestPoint;
            }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

void CustomEclipseItem::setLineItem(CustomLineItem *item, bool isStart){
    lines.push_back(qMakePair(item, isStart));
}

void CustomEclipseItem::updateLinePosition(){
    QPointF center = mapToScene(rect().center());

    for (const auto& lineInfo : lines) {
        CustomLineItem* lineItem = lineInfo.first;
        bool isStartPoint = lineInfo.second;

        QLineF line = lineItem->line();
        if (isStartPoint) {
            line.setP1(center); // Обновляем начальную точку линии
        } else {
            line.setP2(center); // Обновляем конечную точку линии
        }
        lineItem->setLine(line);
        lineItem->getLineText()->setPos( (line.x1() + line.x2()) / 2, (line.y1() + line.y2()) / 2);
    }
}

QPointF CustomEclipseItem::computeTopLeftGridPoint(const QPointF& pointP){
    Scene* customScene = qobject_cast<Scene*> (scene());
    int gridSize = customScene->getGridSize();
    qreal xV = floor(pointP.x()/gridSize)*gridSize;
    qreal yV = floor(pointP.y()/gridSize)*gridSize;
    return QPointF(xV, yV);
}

QRectF CustomEclipseItem::boundingRect() const
{
    return m_boundingRect;
}

void CustomEclipseItem::updateBoundingRect() {
    if (m_points.empty()){
        m_boundingRect = rect();
        return;
    }

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

void CustomEclipseItem::addNeighbor(CustomEclipseItem *eclipseItem){
    if(!neighborsItems.contains(eclipseItem))
        neighborsItems.push_back(eclipseItem);
}

void CustomEclipseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
