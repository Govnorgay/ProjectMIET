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


    toolWindow = new QGroupBox;
    workField = new WorkingField;

    loadBtn = new QPushButton("Load file");
    startAlgBtn1 = new QPushButton("Start Dyakstra");
    startAlgBtn2 = new QPushButton("Start A*");
    matrixWidget = new MatrixWidget;
    setMatrixBtn = new QPushButton("Set Graph");
    addEdgeBtn   = new QPushButton("Add edge");

    toolLayout->setSpacing(0);
    toolLayout->setContentsMargins(0, 0, 0, 0);
    toolLayout->addWidget(loadBtn,  Qt::AlignTop);
    toolLayout->addWidget(startAlgBtn1, Qt::AlignTop);
    toolLayout->addWidget(startAlgBtn2, Qt::AlignTop);
    toolLayout->addWidget(matrixWidget, Qt::AlignTop);
    toolLayout->addWidget(addEdgeBtn, Qt::AlignTop);
    toolLayout->addWidget(setMatrixBtn, Qt::AlignTop);

    toolWindow->setLayout(toolLayout);

    mainLayout->addWidget(workField,  0, 0, 1, 3);
    mainLayout->addWidget(toolWindow, 0, 3);

    connect(addEdgeBtn, SIGNAL(clicked(bool)), workField, SLOT(addEdgeSlot(bool)));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}
