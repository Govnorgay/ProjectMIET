#include "mainwindow.h"
#include <QTest>
#include <QApplication>
#include <TestAlgorithms.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int status = 0;
        {
            TestAlgorithms testCase;
            status |= QTest::qExec(&testCase, argc, argv);
        }

    return a.exec();
}
