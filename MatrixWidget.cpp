#include "MatrixWidget.h"

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
    init();
}

MatrixWidget::~MatrixWidget()
{
}

void MatrixWidget::init(){
    mainLayout = new QGridLayout;

    rowOfMatrixBox = new QSpinBox;
    columnOfMatrixBox = new QSpinBox;

    rowOfMatrixBox->setValue(3);
    columnOfMatrixBox->setValue(3);

    matrix = new QTableWidget(3, 3);
    matrix->setSelectionBehavior(QAbstractItemView::SelectRows);
    matrix->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    matrix->setSelectionMode(QAbstractItemView::ExtendedSelection);
    matrix->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    mainLayout->addWidget(rowOfMatrixBox,    0, 0);
    mainLayout->addWidget(columnOfMatrixBox, 0, 1);
    mainLayout->addWidget(matrix,            1, 0, 1, 2);


    connect(rowOfMatrixBox,    SIGNAL(valueChanged(int)), this, SLOT(rowChangedSlot(int)));
    connect(columnOfMatrixBox, SIGNAL(valueChanged(int)), this, SLOT(columnChangedSlot(int)));

    setLayout(mainLayout);
}

void MatrixWidget::rowChangedSlot(int rows){
    matrix->setRowCount(rows);
}

void MatrixWidget::columnChangedSlot(int column){
    matrix->setColumnCount(column);
}
