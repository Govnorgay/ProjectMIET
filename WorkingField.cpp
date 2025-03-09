#include <WorkingField.h>
#include <QApplication>

WorkingField::WorkingField(QWidget *parent) : QGraphicsView(parent){

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setTransformationAnchor(QGraphicsView::NoAnchor);
    setMouseTracking(true);

    _scene = new Scene(this);
    _scene->setSceneRect(10,10,260,200);


    setScene(_scene);

}

void WorkingField::wheelEvent(QWheelEvent *we){
    if (QApplication::keyboardModifiers() & Qt::ControlModifier){
        if (we->angleDelta().y() < 0)
            updateScale(0.8, _currentPos);
        else
            updateScale(1.25, _currentPos);

        _scene->update();
        update();
    }
    else
        QGraphicsView::wheelEvent(we);

}

void WorkingField::updateScale(const qreal& factor, const QPoint& pos){
    QPointF p1  = mapToScene(pos);

    scale(factor, factor);
    _scaleFactor *= factor;

    QPointF p2 = mapToScene(pos);
    translate(p2.x() - p1.x(), p2.y() - p1.y());
}

void WorkingField::addEdgeSlot(bool){
    CustomRectItem* rectItem1 = new CustomRectItem(0, 0, 60, 60);
    rectItem1->setPos(50,50);
    rectItem1->setBrush(Qt::darkCyan);
    _scene->addItem(rectItem1);
}
