#pragma once

#include <QGraphicsView>
#include "CustomEclipseItem.h"
#include <QTableWidget>
#include <QGraphicsItem>
#include "Scene.h"
#include <QMouseEvent>
#include <QVector>
#include <QPair>
#include <QTime>

class GraphEdge;

class WorkingField : public QGraphicsView{
    Q_OBJECT

public:
    WorkingField(QWidget *parent = nullptr);
    ~WorkingField(){}
protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    Scene* _scene;
    QPointF    _firstSegmentPoint;
    QTransform _defaultTransform;
    QPoint     _currentPos;
    QPointF     _previousPos;
    QPair<QPointF, CustomEclipseItem*> _edgesPair;
    QVector<QPair<QPointF, CustomEclipseItem*>> _edgesVector;
    std::vector<std::vector<int>> matrixInfo;
    QPair<CustomEclipseItem*, CustomEclipseItem*> firstLastItems;

    int rowCount = 0;
    int columnCount = 0;

    bool _isMoving = false;
    int _panStartX;
    int _panStartY;

    float _scaleFactor;
    float _defaultScale;

private:
    double getWeight(CustomEclipseItem* from, CustomEclipseItem* to);
    void updateScale(const qreal& factor, const QPoint& pos);
    void setNeighbors();
    void delay();
public slots:
    void addEdgeSlot(bool);
    void clearAllSlot(bool);
    void setGraphSlot(bool);
    void setRowsCountSlot(int rows){ rowCount = rows;}
    void setColoumnCountSlot(int column){ columnCount = column;}
    void startDeicstraAlgo(bool);

 public:
    QStringList getNodesNames();
    void setMatrixInfo(std::vector<std::vector<int>> matrix);
    void setStartItems(QString item1, QString item2);


};

