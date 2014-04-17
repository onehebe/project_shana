#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dataanalyser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();

    QString currentPath;

    dataAnalyser *analyser;
public slots:
    void openData();
};

#endif // MAINWINDOW_H
