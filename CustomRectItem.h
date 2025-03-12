#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "CustomLineItem.h"
#include "Scene.h"
#include "math.h"

class CustomRectItem : public QGraphicsEllipseItem
{
    QList<QPair<QGraphicsLineItem*, bool>> lines;
public:
    explicit CustomRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,
    const QVariant &value);
private:
    QPointF offset;
    bool isStartPoint = true;
    QList<QPointF> m_points;
    QRectF m_boundingRect = QRectF(0, 0, 60, 60);
    QPointF computeTopLeftGridPoint(const QPointF &pointP);
    void updateBoundingRect();
    void updateLinePosition();
public:
    void setLineItem(CustomLineItem* item, bool isStart);
    QRectF boundingRect() const;
};
