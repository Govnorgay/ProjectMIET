#pragma once

#include <QGraphicsView>
#include "CustomRectItem.h"
#include <QTableWidget>
#include <QGraphicsItem>
#include "Scene.h"
#include <QMouseEvent>
#include <QVector>
#include <QPair>

class GraphEdge;

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
    QPair<QPointF, CustomRectItem*> _edgesPair;
    QVector<QPair<QPointF, CustomRectItem*>> _edgesVector;
    std::vector<std::vector<int>> matrixInfo;

    int rowCount = 0;
    int columnCount = 0;

    bool _isMoving = false;
    int _panStartX;
    int _panStartY;

    float _scaleFactor;
    float _defaultScale;

private:
    void updateScale(const qreal& factor, const QPoint& pos);   
public slots:
    void addEdgeSlot(bool);
    void clearAllSlot(bool);
    void setGraphSlot(bool);
    void setRowsCountSlot(int rows){ rowCount = rows;}
    void setColoumnCountSlot(int column){ columnCount = column;}

 public:
    void setMatrixInfo(std::vector<std::vector<int>> matrix);


};

