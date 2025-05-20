#include <WorkingField.h>
#include <QGraphicsTextItem>
#include <CustomLineItem.h>
#include <QApplication>
#include <mainwindow.h>
#include <cmath>
#include <limits>
#include <queue>
#include <unordered_map>
#include <QDebug>

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
    CustomEclipseItem* rectItem1 = new CustomEclipseItem(0, 0, 60, 60);
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

    double radius = 25.0 * columnCount;

    QPointF center(50, 50);

    // Угловой шаг между элементами
    double angleStep = (2 * M_PI) / columnCount;

    for (int i = 0; i < columnCount; i++) {
        // Вычисляем угол для текущего элемента
        double angle = i * angleStep;

        // Вычисляем координаты элемента
        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);

        // Создаем элемент
        CustomEclipseItem* rectItem1 = new CustomEclipseItem(0, 0, 60, 60);
        QGraphicsTextItem* rectItemText1 = new QGraphicsTextItem(QString("Item%1").arg(i + 1), rectItem1);
        rectItem1->setItemName(QString("Item%1").arg(i + 1));

        QRectF rect = rectItem1->boundingRect();
        rectItemText1->setFont(QFont("Times", 10, QFont::Bold));
        rectItemText1->setPos((rect.center().x() - 20), rect.center().y() - 60);

        rectItem1->setPos(x, y);
        rectItem1->setBrush(Qt::red);
        _scene->addItem(rectItem1);

        // Сохраняем позицию и элемент
        _edgesPair.first = rectItem1->pos();
        _edgesPair.second = rectItem1;
        _edgesVector.push_back(_edgesPair);
    }

    // Отрисовка линий
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            if (matrixInfo.at(i).at(j) != 0) {
                auto rect1 = _edgesVector.at(i).second;
                auto rect2 = _edgesVector.at(j).second;

                // Получаем координаты центров элементов относительно сцены
                QPointF center1 = rect1->mapToScene(rect1->boundingRect().center());
                QPointF center2 = rect2->mapToScene(rect2->boundingRect().center());

                // Создаем линию
                QLineF line(center1, center2);
                CustomLineItem* lineItem = new CustomLineItem(line);
                lineItem->setWieght(matrixInfo.at(i).at(j));

                QGraphicsTextItem* lineWeightText = new QGraphicsTextItem(QString("%1").arg(matrixInfo.at(i).at(j)), lineItem);
                lineWeightText->setFont(QFont("Times", 8, QFont::Bold));
                lineWeightText->setDefaultTextColor(QColor(0, 0, 139));
                lineWeightText->setPos((center1.x() + center2.x())/2,(center1.y() + center2.y())/2);
                lineItem->setLineText(lineWeightText);
                lineItem->setZValue(-1);

                rect1->setLineItem(lineItem, true);
                rect2->setLineItem(lineItem, false);
                // Добавляем линию на сцену
                _scene->addItem(lineItem);
            }
        }
    }
}

void WorkingField::setStartItems(QString item1, QString item2){
    CustomEclipseItem* firstItem = nullptr;
    CustomEclipseItem* secondItem = nullptr;

    for( QPair<QPointF,CustomEclipseItem*> pair : _edgesVector) {
        if(pair.second->getItemName() == item1)
            firstItem = pair.second;

        if(pair.second->getItemName() == item2)
            secondItem = pair.second;
    }
    firstLastItems = qMakePair(firstItem, secondItem);
}

void WorkingField::setNeighbors(){
    for(int vectorPos = 0; vectorPos < _edgesVector.size(); vectorPos++) {
        for(int i = 0; i < matrixInfo[vectorPos].size();  i++){
            _edgesVector[vectorPos].second->setBrush(Qt::red);
            if(matrixInfo[vectorPos][i])
                _edgesVector[vectorPos].second->addNeighbor(_edgesVector[i].second);
        }

    }
}
void WorkingField::startDeicstraAlgo(bool) {
    setNeighbors();
    CustomEclipseItem* startItem = firstLastItems.first;
    CustomEclipseItem* endItem = firstLastItems.second;

    if (!startItem || !endItem)
        return;


    // Структура для хранения расстояний
    std::unordered_map<CustomEclipseItem*, double> distances;
    // Структура для хранения предшественников
    std::unordered_map<CustomEclipseItem*, CustomEclipseItem*> predecessors;

    // Инициализация расстояний
    for (const auto& pair : _edgesVector) {
        distances[pair.second] = std::numeric_limits<double>::infinity();
    }
    distances[startItem] = 0;

    // Приоритетная очередь для выбора вершины с минимальным расстоянием
    auto compare = [&](CustomEclipseItem* a, CustomEclipseItem* b) {
        return distances[a] > distances[b];
    };
    std::priority_queue<CustomEclipseItem*, std::vector<CustomEclipseItem*>, decltype(compare)> queue(compare);
    queue.push(startItem);

    // Основной цикл алгоритма Дейкстры
    while (!queue.empty()) {
        CustomEclipseItem* current = queue.top();
        delay();
        current->setBrush(Qt::yellow);
        queue.pop();

        // Если достигли конечной вершины, завершаем алгоритм
        if (current == endItem) {
            break;
        }

        // Обновляем расстояния до всех соседей
        for (auto& neighbor : current->getNeighbors()) {
            double weight = getWeight(current, neighbor); // Получаем вес ребра
            double newDistance = distances[current] + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                predecessors[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    // Восстановление пути
    if (distances[endItem] == std::numeric_limits<double>::infinity())
        return;

    std::vector<CustomEclipseItem*> path;
    for (CustomEclipseItem* current = endItem; current != nullptr; current = predecessors[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    lastFoundPath = path;
    // Вывод пути
    for (auto item : path) {
        item->setBrush(Qt::green);
        delay();
    }
}

void WorkingField::startAStarAlgo(bool) {
    setNeighbors();

    CustomEclipseItem* startItem = firstLastItems.first;
    CustomEclipseItem* endItem = firstLastItems.second;

    if (!startItem || !endItem) {
        qDebug() << "Start or end item not set!";
        return;
    }

    // Инициализация цветов
    resetAllItemsColor();
    startItem->setBrush(Qt::green);
    delay();

    // Эвристическая функция на основе минимального веса ребра
    auto heuristic = [&](CustomEclipseItem* a, CustomEclipseItem* b) {
        if (!a || !b) return 0.0;
        if (a == b) return 0.0;

        double minWeight = std::numeric_limits<double>::max();
        for (const auto& row : matrixInfo) {
            for (double weight : row) {
                if (weight > 0 && weight < minWeight) {
                    minWeight = weight;
                }
            }
        }
        return minWeight != std::numeric_limits<double>::max() ? minWeight : 0.0;
    };

    // Структуры для алгоритма
    std::unordered_map<CustomEclipseItem*, double> gScore;
    std::unordered_map<CustomEclipseItem*, double> fScore;
    std::unordered_map<CustomEclipseItem*, CustomEclipseItem*> cameFrom;
    std::unordered_map<CustomEclipseItem*, bool> closedSet;

    // Инициализация
    for (const auto& pair : _edgesVector) {
        if (!pair.second) continue;
        gScore[pair.second] = std::numeric_limits<double>::infinity();
        fScore[pair.second] = std::numeric_limits<double>::infinity();
        closedSet[pair.second] = false;
    }
    gScore[startItem] = 0;
    fScore[startItem] = heuristic(startItem, endItem);

    auto compare = [&](CustomEclipseItem* a, CustomEclipseItem* b) {
        if (!a || !b) return false;
        return fScore[a] > fScore[b];
    };

    std::priority_queue<CustomEclipseItem*,
                       std::vector<CustomEclipseItem*>,
                       decltype(compare)> openSet(compare);
    openSet.push(startItem);

    // Основной цикл A*
    while (!openSet.empty()) {
        CustomEclipseItem* current = openSet.top();
        openSet.pop();

        if (!current || closedSet[current]) continue;
        closedSet[current] = true;

        // Безопасная установка цвета
        if (current->scene()) {
            current->setBrush(Qt::yellow);
            delay();
        }

        if (current == endItem) {
            break;
        }

        // Получаем соседей с проверкой
        auto neighbors = current->getNeighbors();
        for (auto& neighbor : neighbors) {
            if (!neighbor || closedSet[neighbor]) continue;

            double edgeWeight = getWeight(current, neighbor);
            if (edgeWeight == std::numeric_limits<double>::infinity()) continue;

            double tentative_gScore = gScore[current] + edgeWeight;

            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, endItem);

                openSet.push(neighbor);
                if (neighbor->scene()) {
                    neighbor->setBrush(Qt::cyan);
                    delay();
                }
            }
        }

        if (current->scene()) {
            current->setBrush(Qt::darkYellow);
            delay();
        }
    }

    // Восстановление пути с проверкой
    if (gScore[endItem] == std::numeric_limits<double>::infinity()) {
        qDebug() << "Path not found!";
        return;
    }

    std::vector<CustomEclipseItem*> path;
    CustomEclipseItem* current = endItem;
    while (current != nullptr && cameFrom.find(current) != cameFrom.end()) {
        path.push_back(current);
        current = cameFrom[current];
    }
    if (current == startItem) {
        path.push_back(startItem);
    }
    std::reverse(path.begin(), path.end());
    lastFoundPath = path;

    // Визуализация пути
    for (auto item : path) {
        if (!item || !item->scene()) continue;
        item->setBrush(Qt::green);
        delay();
    }

    // Выделяем начало и конец
    if (startItem->scene()) {
        startItem->setBrush(Qt::darkGreen);
    }
    if (endItem->scene()) {
        endItem->setBrush(Qt::darkGreen);
    }
}

void WorkingField::resetAllItemsColor() {
    for (const auto& pair : _edgesVector) {
        pair.second->setBrush(Qt::red);  // Исходный цвет
    }
}

double WorkingField::getWeight(CustomEclipseItem* from, CustomEclipseItem* to) {
    // Находим индекс начальной и конечной вершины
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < _edgesVector.size(); i++) {
        if (_edgesVector[i].second == from) {
            fromIndex = i;
        }
        if (_edgesVector[i].second == to) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        qDebug() << "Error: Invalid vertices!";
        return std::numeric_limits<double>::infinity();
    }

    // Возвращаем вес ребра из матрицы смежности
    return matrixInfo[fromIndex][toIndex];
}

QStringList WorkingField::getNodesNames(){
    QStringList nodesNames;
    for( QPair<QPointF,CustomEclipseItem*> pair : _edgesVector){
        nodesNames.push_back(pair.second->getItemName());
    }
    return nodesNames;
}

void WorkingField::delay()
{

    QTime dieTime= QTime::currentTime().addMSecs(3000);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
