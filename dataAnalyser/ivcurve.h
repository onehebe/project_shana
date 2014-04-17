#ifndef IVCURVE_H
#define IVCURVE_H

#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include "qcustomplot.h"
#include "data.h"

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
    QList<bool> layerState;

    QGridLayout *layout;

    void initPlot();
    bool addPlot(Data &data);
    bool setPlot(int index,Data &data);
    bool deletePlot(int index);
    bool replot();

signals:

public slots:

};

#endif // IVCURVE_H
