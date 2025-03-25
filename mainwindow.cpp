#include "mainwindow.h"
#include "QIcon"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    setWindowTitle("GraphVisualizator");
    setWindowIcon(QIcon(":/RC/Vis.png"));
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

    saveBtn = new QPushButton("Save");
    loadBtn = new QPushButton(QIcon(":/RC/load.png"), "");
    loadBtn->setToolTip("Load file");
    matrixWidget = new MatrixWidget;
    setMatrixBtn = new QPushButton("Set Graph");
    removeGraphBtn = new QPushButton("Clear");
    buttonGroup = new QGroupBox;
    buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(loadBtn);
    buttonLayout->addWidget(setMatrixBtn);
    buttonLayout->addWidget(removeGraphBtn);
    buttonGroup->setLayout(buttonLayout);

    rowOfMatrixBox = new QSpinBox;
    columnOfMatrixBox = new QSpinBox;

    algFirstNode = new QComboBox;
    algSecondNode = new QComboBox;
    posLayout = new QHBoxLayout;
    positionGroup = new QGroupBox;


    algFirstNode->setPlaceholderText("Start position");
    algSecondNode->setPlaceholderText("End position");

    posLayout->addWidget(algFirstNode);
    posLayout->addWidget(algSecondNode);
    positionGroup->setLayout(posLayout);

    startAlgBtn2 = new QPushButton("Start A*");
    startAlgBtn1 = new QPushButton("Start Dyakstra");
    algLayout = new QHBoxLayout;
    algoGroup = new QGroupBox;

    algLayout->addWidget(startAlgBtn1);
    algLayout->addWidget(startAlgBtn2);
    algoGroup->setLayout(algLayout);


    matrixLayout->addWidget(rowOfMatrixBox,    0, 0);
    matrixLayout->addWidget(columnOfMatrixBox, 0, 1);
    matrixLayout->addWidget(matrixWidget,      1, 0, 1, 2);

    QWidget* matrix = new QWidget;
    matrix->setLayout(matrixLayout);

    toolLayout->setSpacing(0);
    toolLayout->setContentsMargins(0, 0, 0, 0);   
    toolLayout->addWidget(positionGroup);
    toolLayout->addWidget(algoGroup);
    toolLayout->addWidget(matrix);
    toolLayout->addWidget(buttonGroup);

    toolWindow->setLayout(toolLayout);

    mainLayout->addWidget(workField,  0, 0, 1, 6);
    mainLayout->addWidget(toolWindow, 0, 6, 1, 2);


    connect(setMatrixBtn, SIGNAL(clicked(bool)), this, SLOT(transferMatrixSlot(bool)));
    connect(setMatrixBtn,   SIGNAL(clicked(bool)), workField, SLOT(setGraphSlot(bool)));
    connect(setMatrixBtn,   SIGNAL(clicked(bool)), this, SLOT(setNodesLists(bool)));
    connect(rowOfMatrixBox,    SIGNAL(valueChanged(int)), matrixWidget, SLOT(rowChangedSlot(int)));
    connect(columnOfMatrixBox, SIGNAL(valueChanged(int)), matrixWidget, SLOT(columnChangedSlot(int)));
    connect(rowOfMatrixBox,    SIGNAL(valueChanged(int)), workField, SLOT(setRowsCountSlot(int)));
    connect(columnOfMatrixBox, SIGNAL(valueChanged(int)), workField, SLOT(setColoumnCountSlot(int)));

    connect(startAlgBtn1,   SIGNAL(clicked(bool)), this,      SLOT(setStartLastItems(bool)));
    connect(removeGraphBtn, SIGNAL(clicked(bool)), workField, SLOT(clearAllSlot(bool)));
    connect(startAlgBtn1, SIGNAL(clicked(bool)),   workField, SLOT(startDeicstraAlgo(bool)));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::transferMatrixSlot(bool){
    auto matrix = getMatrixFromTable();
    workField->setMatrixInfo(matrix);
}

void MainWindow::setNodesLists(bool){
    algFirstNode->clear();
    algSecondNode->clear();

    algFirstNode->addItems(workField->getNodesNames());
    algSecondNode->addItems(workField->getNodesNames());
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
            if (item && !item->text().isEmpty()) {
                matrix[row][col] = item->text().toInt();
            }
            // Иначе записываем 0 (значение по умолчанию)
        }
    }

    return matrix;
}

void MainWindow::setStartLastItems(bool){       
    workField->setStartItems(algFirstNode->currentText(), algSecondNode->currentText());
}
