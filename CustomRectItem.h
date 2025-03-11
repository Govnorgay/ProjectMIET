#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "Scene.h"
#include "math.h"

class CustomRectItem : public QGraphicsEllipseItem
{
public:
    explicit CustomRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
    //CustomRectItem(const QRect& rect, QGraphicsItem* parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,
    const QVariant &value);
private:
    QPointF offset;
    QList<QPointF> m_points;
    QRectF m_boundingRect = QRectF(0, 0, 60, 60);
    QPointF computeTopLeftGridPoint(const QPointF &pointP);
    void updateBoundingRect();
public:
    QRectF boundingRect() const;
};
