#include "ivcurve.h"

IVCurve::IVCurve(QWidget *parent) :
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
        this->setLayout(layout);
}

void IVCurve::initPlot()
{
    QFont labelFont;
    QFont trickFont;

    labelFont.setFamily("Times New Roman");
    labelFont.setBold(true);
    labelFont.setPointSize(20);
    trickFont.setFamily("Times New Roman");
    trickFont.setBold(true);
    labelFont.setPointSize(15);

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
    plot->xAxis->setRange(0,1);
    plot->yAxis->setTickStep(5);
    plot->yAxis->setSubTickCount(4);
    plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
    plot->xAxis2->setScaleLogBase(10);
    plot->xAxis2->setSubTickCount(4);
    plot->xAxis2->setRangeLower(1e-12);
    plot->xAxis2->setNumberFormat("ebc");
    plot->xAxis2->setNumberPrecision(0);
    plot->xAxis2->setTickStep(100);

    plot->xAxis->setLabelFont(labelFont);
    plot->xAxis->setTickLabelFont(labelFont);
    plot->yAxis->setLabelFont(labelFont);
    plot->yAxis->setTickLabelFont(labelFont);
    plot->xAxis2->setLabelFont(labelFont);
    plot->xAxis2->setTickLabelFont(labelFont);
    plot->yAxis2->setLabelFont(labelFont);
    plot->yAxis2->setTickLabelFont(labelFont);
}

bool IVCurve::addPlot(Data &data)
{

    plot->clearPlottables();

    QCPCurve *msCurve = new QCPCurve(plot->yAxis,plot->xAxis);
    QCPCurve *lkCurve = new QCPCurve(plot->yAxis,plot->xAxis2);

    plot->addPlottable(msCurve);
    plot->addPlottable(lkCurve);

    plotCount ++;
    msCurve->setName(QString("Measurement").append(QString::number(plotCount)));
    lkCurve->setName(QString("Leakage").append(QString::number(plotCount)));
    msCurve->setData(data.count,data.current,data.voltage);
    lkCurve->setData(data.count,data.current,data.leakage);

    QPen redPen;
    QPen bluePen;
    QCPScatterStyle redScatter;
    QCPScatterStyle blueScatter;

    redPen.setColor(Qt::red);
    redPen.setWidth(2.0);
    bluePen.setColor(Qt::blue);
    bluePen.setWidth(1.0);

    redScatter.setPen(QPen(Qt::black));
    redScatter.setBrush(QBrush(Qt::red));
    redScatter.setShape(QCPScatterStyle::ssCircle);
    blueScatter.setPen(QPen(Qt::blue));
    blueScatter.setBrush(QBrush(Qt::blue));
    blueScatter.setShape(QCPScatterStyle::ssTriangleInverted);

    msCurve->setScatterStyle(redScatter);
    lkCurve->setScatterStyle(blueScatter);

    msCurve->setPen(redPen);
    lkCurve->setPen(bluePen);

    double upperVoltage = ceil(data.voltage.at(data.getMaximumVoltageIndex())/5.0)*5.0 + 0.1;
    //if (upperVoltage > plot->xAxis->range().upper){
        plot->xAxis->setRangeLower(0);
        plot->xAxis->setRangeUpper(upperVoltage);
    //}

    double upperCurrent = ceil(data.current.at(data.getMaximumCurrentIndex()));
    //if (upperCurrent > plot->yAxis->range().upper){
        plot->yAxis->setRangeLower(0);
        plot->yAxis->setRangeUpper(upperCurrent);
        plot->yAxis2->setRangeUpper(upperCurrent);
    //}

    plot->replot();

    return true;
}

bool IVCurve::setPlot(int index, Data &data)
{
    if (plot->plottableCount()<(index*2+1))
        return false;
    dynamic_cast<QCPCurve*>(plot->plottable(index*2))->setData(data.count,data.current,data.voltage);
    dynamic_cast<QCPCurve*>(plot->plottable(index*2+1))->setData(data.count,data.current,data.leakage);

    return true;
}

bool IVCurve::deletePlot(int index)
{
    if (plot->plottableCount()<(index*2+1))
        return false;
    plot->removePlottable(index*2);
    plot->removePlottable(index*2);
    return true;
}

bool IVCurve::replot()
{
    plot->replot();
    return true;
}
