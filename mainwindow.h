#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <WorkingField.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <MatrixWidget.h>
#include <QGroupBox>
#include <QSpinBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QGridLayout*  mainLayout;
    QVBoxLayout*  toolLayout;
    QGridLayout*  matrixLayout;
    MatrixWidget* matrixWidget;
    WorkingField* workField;
    QPushButton*  loadBtn;
    QPushButton*  startAlgBtn1;
    QPushButton*  startAlgBtn2;
    QPushButton*  setMatrixBtn;
    QPushButton*  addEdgeBtn;
    QPushButton*  removeGraphBtn;
    QGroupBox*    toolWindow;
    QSpinBox*     rowOfMatrixBox;
    QSpinBox*     columnOfMatrixBox;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init();
    std::vector<std::vector<int>>getMatrixFromTable();
private slots:
    void transferMatrixSlot(bool);

};

