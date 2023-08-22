#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    throw "my deliberate excetion";
}

MainWindow::~MainWindow()
{
    delete ui;
}

