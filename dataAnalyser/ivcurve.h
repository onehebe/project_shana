#ifndef IVCURVE_H
#define IVCURVE_H

#include <QWidget>
#include <QGridLayout>
#include "../qcustomplot/qcustomplot.h"
#include "../dataReader/data.h"

class IVcurve : public QWidget
{
    Q_OBJECT
public:
    explicit IVcurve(QWidget *parent = 0);

    QCustomPlot *plot;

    int plotCount;
    int plotIndex;
    bool isMeasurementOn;
    bool isLeakageOn;
    QList<bool> layerState;

    QGridLayout *layout;
private:
    void initPlot();
    bool addPlot(Data &data);
    bool setPlot(int index,Data &data);
    bool deletePlot(int index);
    bool replot();

signals:

public slots:

};

#endif // IVCURVE_H
