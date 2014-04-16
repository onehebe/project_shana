#include "ivcurve.h"

IVcurve::IVcurve(QWidget *parent) :
    QWidget(parent)
{
        plot = new QCustomPlot();
        plotCount = 0;
        plotIndex = 0;
        isMeasurementOn = true;
        isLeakageOn = true;

        layerState.clear();

        initPlot();

        layout = new QGridLayout();
        layout->addWidget(plot,0,0);
}

void IVcurve::initPlot()
{
    plot->xAxis->setVisible(true);
    plot->xAxis2->setVisible(true);
    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);

    plot->xAxis->setLabel(tr("Voltage (V)"));
    plot->yAxis->setLabel(tr("Current (A)"));
    plot->xAxis2->setLabel(tr("Leakage Current (A)"));
    plot->yAxis2->setLabel(tr("Current (A)"));

    plot->xAxis->grid()->setVisible(false);
    plot->yAxis->grid()->setVisible(true);
    plot->yAxis->grid()->setPen(QPen(Qt::blue,1,Qt::DashDotDotLine));
    plot->xAxis2->grid()->setVisible(true);
    plot->xAxis2->grid()->setSubGridVisible(true);
    plot->xAxis2->grid()->setSubGridPen(QPen(Qt::lightGray,0.5,Qt::DashDotDotLine));
    plot->xAxis2->grid()->setPen(QPen(Qt::green,1,Qt::DashDotDotLine));
    plot->yAxis2->grid()->setVisible(false);

    plot->xAxis->setScaleType(QCPAxis::stLinear);
    plot->xAxis->setSubTickCount(4);
    plot->yAxis->setTickStep(1);
    plot->yAxis->setSubTickCount(4);
    plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
    plot->xAxis2->setScaleLogBase(10);
    plot->xAxis2->setSubTickCount(4);
    plot->xAxis2->setRangeLower(1e-10);
    plot->xAxis2->setNumberFormat("ebc");
    plot->xAxis2->setNumberPrecision(0);
}

bool IVcurve::addPlot(Data &data)
{

    QCPCurve *msCurve = new QCPCurve(plot->yAxis,plot->xAxis);
    QCPCurve *lkCurve = new QCPCurve(plot->yAxis,plot->xAxis2);

    plot->addPlottable(msCurve);
    plot->addPlottable(lkCurve);

    plotCount ++;
    msCurve->setName(QString("Measurement").append(QString::number(plotCount)));
    lkCurve->setName(QString("Leakage").append(QString::number(plotCount)));
    msCurve->setData(data.count,data.current,data.voltage);
    lkCurve->setData(data.count,data.current,data.leakage);

    return true;
}

bool IVcurve::setPlot(int index, Data &data)
{
    if (plot->plottableCount()<(index*2+1))
        return false;
    dynamic_cast<QCPCurve*>(plot->plottable(index*2))->setData(data.count,data.current,data.voltage);
    dynamic_cast<QCPCurve*>(plot->plottable(index*2+1))->setData(data.count,data.current,data.leakage);

    return true;
}

bool IVcurve::deletePlot(int index)
{
    if (plot->plottableCount()<(index*2+1))
        return false;
    plot->removePlottable(index*2);
    plot->removePlottable(index*2);
    return true;
}

bool IVcurve::replot()
{
    plot->replot();
    return true;
}
