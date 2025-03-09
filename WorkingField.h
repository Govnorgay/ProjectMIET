#pragma once

#include <QGraphicsView>
#include "CustomRectItem.h"
#include <QGraphicsItem>
#include "Scene.h"
#include <QMouseEvent>
#include <QMap>

class WorkingField : public QGraphicsView{
    Q_OBJECT

public:
    WorkingField(QWidget *parent = nullptr);
    ~WorkingField(){}
protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene* _scene;
    QPointF    _firstSegmentPoint;
    QTransform _defaultTransform;
    QPoint     _currentPos;
    QPointF     _previousPos;

    bool _isMoving = false;
    int _panStartX;
    int _panStartY;

    float _scaleFactor;
    float _defaultScale;

private:
    void updateScale(const qreal& factor, const QPoint& pos);   
public slots:
    void addEdgeSlot(bool);

};

