#pragma once
#include <QGraphicsView>
#include <QTableWidget>
#include <QSpinBox>
#include <QGridLayout>
#include <QHeaderView>

class MatrixWidget : public QWidget
{
    Q_OBJECT

    QGridLayout*  mainLayout;
    QSpinBox*     rowOfMatrixBox;
    QSpinBox*     columnOfMatrixBox;
    QTableWidget* matrix;

public:
    MatrixWidget(QWidget *parent = nullptr);
    ~MatrixWidget();
private:
    void init();
public slots:
    void rowChangedSlot(int rows);
    void columnChangedSlot(int columns);
};

