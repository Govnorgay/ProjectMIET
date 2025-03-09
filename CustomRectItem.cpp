#include "CustomRectItem.h"

//CustomRectItem::CustomRectItem(const QRect& rect, QGraphicsItem* parent):
//    QGraphicsRectItem(rect, parent)
//{
//    setFlags(QGraphicsItem::ItemIsSelectable |
//            QGraphicsItem::ItemIsMovable |
//            QGraphicsItem::ItemSendsGeometryChanges);
//}


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
}

QVariant CustomRectItem::itemChange(GraphicsItemChange change,
const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
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

QPointF CustomRectItem::computeTopLeftGridPoint(const QPointF& pointP){
    Scene* customScene = qobject_cast<Scene*> (scene());
    int gridSize = customScene->getGridSize();
    qreal xV = floor(pointP.x()/gridSize)*gridSize;
    qreal yV = floor(pointP.y()/gridSize)*gridSize;
    return QPointF(xV, yV);
}
