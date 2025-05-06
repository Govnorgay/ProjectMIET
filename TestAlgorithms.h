#pragma once
#include <QtTest>
#include "WorkingField.h"

class TestAlgorithms : public QObject
{
    Q_OBJECT
    public:
        explicit TestAlgorithms(QObject *parent = 0);

private:
    WorkingField* wf;
    Scene* testScene;

private slots:
    void initTestCase();     // Инициализация перед всеми тестами
    void cleanupTestCase();  // Очистка после всех тестов
    void testDijkstraBasic();
    void testAStarBasic();
};
