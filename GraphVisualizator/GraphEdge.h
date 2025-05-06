#pragma once

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class GraphEdge : public QGraphicsRectItem
{
public:
    explicit GraphEdge(const QRect& rect, QGraphicsItem* parent = 0);
    ~GraphEdge();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateBoundingRect();
    QPointF computeTopLeftGridPoint(const QPointF &pointP);

    QList<QPointF> m_points;
    QRectF m_boundingRect;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QPointF offset;
    QString EdgeName;
};
