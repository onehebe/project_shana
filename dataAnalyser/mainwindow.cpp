#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget();
    analyser = new dataAnalyser(this);
    designer = new layoutDesigner(this);
    manager = new dataBaseManager(this);

    tabWidget->addTab(analyser,"Data");
    tabWidget->addTab(designer,"layout");
    tabWidget->addTab(manager,"database");

    this->setCentralWidget(tabWidget);
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
    this->setMenuBar(analyser->menuBar);
    this->setStatusBar(analyser->statusBar);
}

MainWindow::~MainWindow()
{

}
