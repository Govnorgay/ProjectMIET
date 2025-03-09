#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <WorkingField.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <MatrixWidget.h>
#include <QGroupBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QGridLayout*  mainLayout;
    QVBoxLayout*  toolLayout;

    WorkingField* workField;
    QPushButton*  loadBtn;
    QPushButton*  startAlgBtn1;
    QPushButton*  startAlgBtn2;
    MatrixWidget* matrixWidget;
    QPushButton*  setMatrixBtn;
    QPushButton*  addEdgeBtn;
    QGroupBox*  toolWindow;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init();
};

