#ifndef IVCURVE_H
#define IVCURVE_H

#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include "qcustomplot.h"
#include "data.h"

#define MIN_CUR 1e-3
#define MIN_VOL 1e-2
#define MIN_LEAKAGE 1e-11

class IVCurve : public QWidget
{
    Q_OBJECT
public:
    explicit IVCurve(QWidget *parent = 0);

    QCustomPlot *plot;

    int plotCount;
    int plotIndex;
    bool isMeasurementOn;
    bool isLeakageOn;
    //QList<bool> layerState;
    QList<Data*> dataList;

    QGridLayout *layout;
    QGroupBox *figure;
    QGroupBox *yAxisOption;
    QGroupBox *xAxis2Option;
    QGroupBox *layerOption;

    QButtonGroup *yAxisGroup;
    QButtonGroup *xAxis2Group;
    QButtonGroup *layerGroup;

    QRadioButton *yAxisLog;
    QRadioButton *yAxisLinear;
    QRadioButton *xAxis2Log;
    QRadioButton *xAxis2Linear;

    QCheckBox *measurement;
    QCheckBox *leakage;

    void initPlot();
    void initAxisOption();

    bool reScale();
    bool reScaleVoltage();
    bool reScaleCurrent();
    bool reScaleLeakage();

    bool addPlot(Data &data);
    bool setPlot(int index,Data &data);
    bool deletePlot(int index);
    bool replot();

signals:

public slots:
    void setXAxis2ScaleType(int id);
    void setYAxisScaleType(int id);
};
#endif // IVCURVE_H
