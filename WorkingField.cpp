#include <WorkingField.h>
#include <QGraphicsTextItem>
#include "CustomLineItem.h"
#include <QApplication>
#include <mainwindow.h>
#include <cmath>

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

    update();

}

void WorkingField::updateScale(const qreal& factor, const QPoint& pos){
    QPointF p1  = mapToScene(pos);

    scale(factor, factor);
    _scaleFactor *= factor;

    QPointF p2 = mapToScene(pos);
    translate(p2.x() - p1.x(), p2.y() - p1.y());
    update();
}

void WorkingField::addEdgeSlot(bool){
    CustomRectItem* rectItem1 = new CustomRectItem(0, 0, 60, 60);
    rectItem1->setPos(50,50);
    rectItem1->setBrush(Qt::darkCyan);
    _scene->addItem(rectItem1);
    _edgesPair.first = rectItem1->pos();
    _edgesPair.second = rectItem1;
    _edgesVector.push_back(_edgesPair);
}

void WorkingField::clearAllSlot(bool){
    _scene->clear();
    _edgesVector.clear();
}

void WorkingField::setMatrixInfo(std::vector<std::vector<int>> matrix) {
    matrixInfo = matrix;
}

void WorkingField::setGraphSlot(bool) {
    if (rowCount != columnCount)
        return;
    clearAllSlot(true);

    // Радиус окружности
    double radius = 200.0;

    // Центр окружности
    QPointF center(50, 50); // Можете изменить на нужные координаты

    // Угловой шаг между элементами
    double angleStep = (2 * M_PI) / columnCount; // 2 * M_PI — это полный круг (360 градусов)

    for (int i = 0; i < columnCount; i++) {
        // Вычисляем угол для текущего элемента
        double angle = i * angleStep;

        // Вычисляем координаты элемента
        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);

        // Создаем элемент
        CustomRectItem* rectItem1 = new CustomRectItem(0, 0, 60, 60);
        QGraphicsTextItem* rectItemText1 = new QGraphicsTextItem(QString("Item %1").arg(i + 1), rectItem1);

        QRectF rect = rectItem1->boundingRect();
        rectItemText1->setFont(QFont("Times", 10, QFont::Bold));
        rectItemText1->setPos((rect.center().x() - 20), rect.center().y() - 60);

        rectItem1->setPos(x, y);
        rectItem1->setBrush(Qt::darkCyan);
        _scene->addItem(rectItem1);

        // Сохраняем позицию и элемент
        _edgesPair.first = rectItem1->pos();
        _edgesPair.second = rectItem1;
        _edgesVector.push_back(_edgesPair);
    }

    // Отрисовка линий
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            if (matrixInfo.at(i).at(j) == 1) {
                auto rect1 = _edgesVector.at(i).second;
                auto rect2 = _edgesVector.at(j).second;

                // Получаем координаты центров элементов относительно сцены
                QPointF center1 = rect1->mapToScene(rect1->boundingRect().center());
                QPointF center2 = rect2->mapToScene(rect2->boundingRect().center());

                // Создаем линию
                QLineF line(center1, center2);
                CustomLineItem* lineItem = new CustomLineItem(line);

                lineItem->setZValue(1);
                rect1->setLineItem(lineItem, true);
                rect2->setLineItem(lineItem, false);
                // Добавляем линию на сцену
                _scene->addItem(lineItem);
            }
        }
    }
}
