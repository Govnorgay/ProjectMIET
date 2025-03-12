#include "MatrixWidget.h"

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

    layout->addWidget(matrix);

    this->setLayout(layout);

}

void MatrixWidget::rowChangedSlot(int rows){
    matrix->setRowCount(rows);
}

void MatrixWidget::columnChangedSlot(int column){
    matrix->setColumnCount(column);
}
