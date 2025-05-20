#include <QTest>
#include "TestAlgorithms.h"

TestAlgorithms::TestAlgorithms(QObject *parent) :
    QObject(parent)
{
}

void TestAlgorithms::initTestCase()
{
    wf = new WorkingField();
    testScene = new Scene();
    wf->_scene = testScene;

    // Создаем тестовый граф:
    // A -> B (2)
    // B -> C (3)
    // A -> C (10)
    std::vector<std::vector<int>> testMatrix = {
        {0, 2, 10},
        {0, 0, 3},
        {0, 0, 0}
    };

    wf->rowCount = wf->columnCount = 3;
    wf->setMatrixInfo(testMatrix);
    wf->setGraphSlot(true);
}

void TestAlgorithms::cleanupTestCase()
{
    delete wf;
}

void TestAlgorithms::testDijkstraBasic()
{
    // Устанавливаем начальную и конечную точки
    wf->setStartItems("Item1", "Item3");

    // Запускаем алгоритм
    wf->startDeicstraAlgo(true);

    // Проверяем результат
    auto path = wf->getLastFoundPath();  // Предполагается добавление метода getLastFoundPath()
    QVERIFY(!path.empty());
    QCOMPARE(path.size(), 3);
    QCOMPARE(path[0]->getItemName(), "Item1");
    QCOMPARE(path[1]->getItemName(), "Item2");
    QCOMPARE(path[2]->getItemName(), "Item4");
}

void TestAlgorithms::testAStarBasic()
{
    wf->setStartItems("Item1", "Item3");
    wf->startAStarAlgo(true);

    auto path = wf->getLastFoundPath();
    QVERIFY(!path.empty());
    QCOMPARE(path.size(), 3);
    QCOMPARE(path[0]->getItemName(), "Item1");
    QCOMPARE(path[1]->getItemName(), "Item2");
    QCOMPARE(path[2]->getItemName(), "Item3");
}

