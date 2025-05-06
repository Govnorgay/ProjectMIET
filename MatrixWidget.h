#pragma once
#include <QGraphicsView>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>

class MatrixWidget : public QWidget
{
    Q_OBJECT  

public:
    MatrixWidget(QWidget *parent = nullptr);
    QTableWidget* matrix;
    QVBoxLayout* layout;
    ~MatrixWidget();
private:
    void init();
public slots:
    void rowChangedSlot(int rows);
    void columnChangedSlot(int columns);
    void duplicateCellValue(int row, int column);
    void setMatrix(std::vector<std::vector<int>> matrix);
};

