#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget();
    analyser = new dataAnalyser(this);

    tabWidget->addTab(analyser,"Data");

    this->setCentralWidget(tabWidget);
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
    this->setMenuBar(analyser->menuBar);
}

MainWindow::~MainWindow()
{

}
