#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataanalyser.h"
#include "layoutdesigner.h"
#include "databasemanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTabWidget *tabWidget;
    dataAnalyser *analyser;
    layoutDesigner *designer;
    dataBaseManager *manager;
};

#endif // MAINWINDOW_H
