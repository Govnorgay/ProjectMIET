#include "MatrixWidget.h"
#include "CustomDelegate.h"

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
    init();
}

MatrixWidget::~MatrixWidget()
{
}

void MatrixWidget::init(){

    layout = new QVBoxLayout;

    matrix = new QTableWidget;
    matrix->setSelectionBehavior(QAbstractItemView::SelectRows);
    matrix->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    matrix->setSelectionMode(QAbstractItemView::ExtendedSelection);
    matrix->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    matrix->setItemDelegate(new CustomDelegate(matrix));
    connect(matrix, SIGNAL(cellChanged(int,int)), this, SLOT(duplicateCellValue(int,int)));

    layout->addWidget(matrix);

    this->setLayout(layout);

}

void MatrixWidget::duplicateCellValue(int row, int column){
    matrix->blockSignals(1);
    matrix->setItem(row, column, new QTableWidgetItem(matrix->item(row, column)->text()));
    matrix->blockSignals(0);
}

void MatrixWidget::rowChangedSlot(int rows){
    matrix->setRowCount(rows);
}

void MatrixWidget::columnChangedSlot(int column){
    matrix->setColumnCount(column);
}

void MatrixWidget::setMatrix(std::vector<std::vector<int> > matrixFromFile){
    matrix->blockSignals(1);
    rowChangedSlot(matrixFromFile.size());
    columnChangedSlot(matrixFromFile.size());
    for(int row = 0; row < matrixFromFile.size(); row++){
        for(int column = 0; column < matrixFromFile.at(row).size(); column++){
            matrix->setItem(row, column, new QTableWidgetItem(QString::number(matrixFromFile.at(row).at(column))));
        }
    }
    matrix->blockSignals(0);
}
