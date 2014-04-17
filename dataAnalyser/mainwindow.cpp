#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    analyser = new dataAnalyser(this);
    this->setCentralWidget(analyser);
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
    currentPath = "./";
    createActions();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = new QAction(tr("&Open"),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(openData()));

    fileMenu->addAction(openAction);

}

void MainWindow::openData()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open File"),currentPath);
    currentPath = QDir(file).path();
    if (!file.isEmpty()){
        qDebug() << analyser->analyze(file);
    }

}
