#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include "CustomLineItem.h"
#include "Scene.h"
#include "math.h"

class CustomEclipseItem : public QGraphicsEllipseItem
{
    QList<QPair<CustomLineItem*, bool>> lines;
    QVector<CustomEclipseItem*> neighborsItems;
    QString itemName;
public:
    explicit CustomEclipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
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
    void setItemName(QString name){itemName = name;}
    void addNeighbor(CustomEclipseItem* eclipseItem);
    QVector<CustomEclipseItem*> getNeighbors() {return neighborsItems;}
    QString getItemName(){ return itemName;}
    QRectF boundingRect() const;
};
