#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    setWindowTitle("GraphVisualizator");
    resize(900, 600);
    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
}

void MainWindow::init(){
    mainLayout = new QGridLayout;
    toolLayout = new QVBoxLayout;
    matrixLayout = new QGridLayout;

    toolWindow = new QGroupBox;
    workField = new WorkingField;

    loadBtn = new QPushButton("Load file");
    startAlgBtn1 = new QPushButton("Start Dyakstra");
    startAlgBtn2 = new QPushButton("Start A*");
    matrixWidget = new MatrixWidget;
    setMatrixBtn = new QPushButton("Set Graph");
    addEdgeBtn   = new QPushButton("Add edge");
    removeGraphBtn = new QPushButton("Clear");
    rowOfMatrixBox = new QSpinBox;
    columnOfMatrixBox = new QSpinBox;

    matrixLayout->addWidget(rowOfMatrixBox,    0, 0);
    matrixLayout->addWidget(columnOfMatrixBox, 0, 1);
    matrixLayout->addWidget(matrixWidget,      1, 0, 1, 2);

    QWidget* matrix = new QWidget;
    matrix->setLayout(matrixLayout);

    toolLayout->setSpacing(0);
    toolLayout->setContentsMargins(0, 0, 0, 0);
    toolLayout->addWidget(loadBtn,  Qt::AlignTop);
    toolLayout->addWidget(startAlgBtn1, Qt::AlignTop);
    toolLayout->addWidget(startAlgBtn2, Qt::AlignTop);
    toolLayout->addWidget(matrix,       Qt::AlignTop);
    toolLayout->addWidget(addEdgeBtn, Qt::AlignTop);
    toolLayout->addWidget(removeGraphBtn, Qt::AlignTop);
    toolLayout->addWidget(setMatrixBtn, Qt::AlignTop);

    toolWindow->setLayout(toolLayout);

    mainLayout->addWidget(workField,  0, 0, 1, 3);
    mainLayout->addWidget(toolWindow, 0, 3);

    connect(addEdgeBtn, SIGNAL(clicked(bool)), workField, SLOT(addEdgeSlot(bool)));
    connect(removeGraphBtn, SIGNAL(clicked(bool)), workField, SLOT(clearAllSlot(bool)));
    connect(setMatrixBtn, SIGNAL(clicked(bool)), this, SLOT(transferMatrixSlot(bool)));
    connect(setMatrixBtn,   SIGNAL(clicked(bool)), workField, SLOT(setGraphSlot(bool)));
    connect(rowOfMatrixBox,    SIGNAL(valueChanged(int)), matrixWidget, SLOT(rowChangedSlot(int)));
    connect(columnOfMatrixBox, SIGNAL(valueChanged(int)), matrixWidget, SLOT(columnChangedSlot(int)));
    connect(rowOfMatrixBox,    SIGNAL(valueChanged(int)), workField, SLOT(setRowsCountSlot(int)));
    connect(columnOfMatrixBox, SIGNAL(valueChanged(int)), workField, SLOT(setColoumnCountSlot(int)));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::transferMatrixSlot(bool){
    auto matrix = getMatrixFromTable();
    workField->setMatrixInfo(matrix);
}

std::vector<std::vector<int>> MainWindow::getMatrixFromTable() {
    // Получаем количество строк и столбцов в таблице
    int rowCount = matrixWidget->matrix->rowCount();
    int columnCount = matrixWidget->matrix->columnCount();

    // Создаем двумерный вектор (массив) для хранения результата
    std::vector<std::vector<int>> matrix(rowCount, std::vector<int>(columnCount, 0));

    // Проходим по всем ячейкам таблицы
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            // Получаем элемент ячейки
            QTableWidgetItem* item = matrixWidget->matrix->item(row, col);

            // Если ячейка существует и её текст равен "1", записываем 1 в массив
            if (item && item->text() == "1") {
                matrix[row][col] = 1;
            }
            // Иначе записываем 0 (значение по умолчанию)
        }
    }

    return matrix;
}
