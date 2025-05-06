#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <WorkingField.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <MatrixWidget.h>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QGridLayout*  mainLayout;
    QVBoxLayout*  toolLayout;
    QGridLayout*  matrixLayout;
    MatrixWidget* matrixWidget;
    WorkingField* workField;

    QComboBox*    algFirstNode;
    QComboBox*    algSecondNode;
    QPushButton*  startAlgBtn1;
    QGroupBox*    positionGroup;
    QGroupBox*    algoGroup;
    QHBoxLayout*  posLayout;
    QHBoxLayout*  algLayout;

    QPushButton*  saveBtn;
    QPushButton*  loadBtn;
    QPushButton*  startAlgBtn2;
    QPushButton*  setMatrixBtn;
    QPushButton*  removeGraphBtn;
    QGroupBox*    toolWindow;
    QGroupBox*    buttonGroup;
    QHBoxLayout*  buttonLayout;
    QSpinBox*     rowOfMatrixBox;
    QSpinBox*     columnOfMatrixBox;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init();
    std::vector<std::vector<int>>getMatrixFromTable();
private slots:
    void setNodesLists(bool);
    void transferMatrixSlot(bool);
    void setStartLastItems(bool);

};

