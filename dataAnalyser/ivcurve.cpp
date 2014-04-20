#include "ivcurve.h"

IVCurve::IVCurve(QWidget *parent) :
    QWidget(parent)
{
        plot = new QCustomPlot();
        plotCount = 0;
        plotIndex = 0;
        isMeasurementOn = true;
        isLeakageOn = true;

        //layerState.clear();

        initPlot();

        figure = new QGroupBox(tr("Figure"));
        QGridLayout *figLyt = new QGridLayout();
        figLyt->addWidget(plot,0,0);
        figure->setLayout(figLyt);

        layout = new QGridLayout();
        layout->addWidget(figure,0,0);
        this->setLayout(layout);

        initAxisOption();
}

QPixmap IVCurve::getPixmap(int w, int h)
{
    return plot->toPixmap(w,h);
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
    labelFont.setPointSize(10);

    plot->xAxis->setVisible(true);
    plot->xAxis2->setVisible(true);
    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->legend->setVisible(true);

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
    plot->xAxis->setRange(0,5);
    plot->xAxis->setAutoTickStep(false);
    plot->xAxis->setTickStep(5);
    plot->yAxis->setAutoTickStep(false);
    plot->yAxis->setSubTickCount(4);
    plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
    plot->xAxis2->setScaleLogBase(100);
    plot->xAxis2->setSubTickCount(4);
    plot->xAxis2->setRangeLower(1e-12);
    plot->xAxis2->setNumberFormat("ebc");
    plot->xAxis2->setNumberPrecision(0);
    plot->yAxis2->setAutoTickStep(false);
    plot->yAxis2->setSubTickCount(4);

    plot->xAxis->setLabelFont(labelFont);
    plot->xAxis->setTickLabelFont(labelFont);
    plot->yAxis->setLabelFont(labelFont);
    plot->yAxis->setTickLabelFont(labelFont);
    plot->xAxis2->setLabelFont(labelFont);
    plot->xAxis2->setTickLabelFont(labelFont);
    plot->yAxis2->setLabelFont(labelFont);
    plot->yAxis2->setTickLabelFont(labelFont);


    plot->setAutoAddPlottableToLegend(true);
    plot->legend->setFont(trickFont);
}

void IVCurve::initAxisOption()
{
    layerOption = new QGroupBox(tr("Display:"));
    layerGroup =new QButtonGroup();
    measurement = new QCheckBox(tr("Measurement"));
    leakage = new QCheckBox(tr("Leakage"));
    legend = new QCheckBox(tr("Legend"));
    layerGroup->setExclusive(false);
    measurement->setChecked(true);
    leakage->setChecked(true);
    legend->setChecked(true);
    layerGroup->addButton(measurement);
    layerGroup->addButton(leakage);
    layerGroup->addButton(legend);
    QVBoxLayout *layerLyt = new QVBoxLayout();
    layerLyt->addWidget(measurement);
    layerLyt->addWidget(leakage);
    layerLyt->addWidget(legend);

    layerOption->setLayout(layerLyt);
    layerOption->setMaximumHeight(100);
    layerOption->setMaximumWidth(150);

    yAxisOption = new QGroupBox(tr("Current scale:"));
    yAxisGroup = new QButtonGroup();
    yAxisLinear = new QRadioButton(tr("Liner"));
    yAxisLog = new QRadioButton(tr("Log"));
    yAxisLinear->setChecked(true);
    yAxisGroup->addButton(yAxisLinear);
    yAxisGroup->addButton(yAxisLog);
    yAxisGroup->setExclusive(true);
    QVBoxLayout *yAxisLyt = new QVBoxLayout();
    yAxisLyt->addWidget(yAxisLinear);
    yAxisLyt->addWidget(yAxisLog);
    yAxisOption->setLayout(yAxisLyt);
    yAxisOption->setMaximumHeight(80);
    yAxisOption->setMaximumWidth(150);

    xAxis2Option = new QGroupBox(tr("Leakage scale:"));
    xAxis2Group = new QButtonGroup();
    xAxis2Linear = new QRadioButton(tr("Liner"));
    xAxis2Log = new QRadioButton(tr("Log"));
    xAxis2Log->setChecked(true);
    xAxis2Group->addButton(xAxis2Linear);
    xAxis2Group->addButton(xAxis2Log);
    xAxis2Group->setExclusive(true);
    QVBoxLayout *xAxis2Lyt = new QVBoxLayout();
    xAxis2Lyt->addWidget(xAxis2Linear);
    xAxis2Lyt->addWidget(xAxis2Log);
    xAxis2Option->setLayout(xAxis2Lyt);
    xAxis2Option->setMaximumHeight(80);
    xAxis2Option->setMaximumWidth(150);

    QVBoxLayout *leftPanel = new QVBoxLayout();
    leftPanel->addWidget(layerOption);
    leftPanel->addWidget(yAxisOption);
    leftPanel->addWidget(xAxis2Option);
    leftPanel->addStretch();

    layout->addLayout(leftPanel,0,1);

    connect(yAxisGroup,SIGNAL(buttonClicked(int)),this,SLOT(setYAxisScaleType(int)));
    connect(xAxis2Group,SIGNAL(buttonClicked(int)),this,SLOT(setXAxis2ScaleType(int)));
    connect(layerGroup,SIGNAL(buttonClicked(int)),this,SLOT(setDisplayable(int)));
}

bool IVCurve::addPlot(Data &data)
{

    plot->clearPlottables();

    QCPCurve *msCurve = new QCPCurve(plot->yAxis,plot->xAxis);
    QCPCurve *lkCurve = new QCPCurve(plot->yAxis,plot->xAxis2);

    plot->addPlottable(msCurve);
    plot->addPlottable(lkCurve);

    //plotCount ++;
    //msCurve->setName(QString("Measurement").append(QString::number(plotCount)));
    //lkCurve->setName(QString("Leakage").append(QString::number(plotCount)));
    msCurve->setName(QString("Measurement"));
    lkCurve->setName(QString("Leakage"));
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

    if(dataList.isEmpty())
        dataList.append(&data);
    else{
        dataList.clear();
        dataList.append(&data);
    }

    reScale();

    plot->replot();

    return true;
}

/*****************************************************
 *                  rescale strategy:
 * Measurent Voltage:
 *      maximum:    if maxVoltage <= MIN_VOL then
 *                      voltage.upperRange = 0;
 *                  else if maxVoltage < 5 then
 *                      voltage.upperRange = 5;
 *                      voltage.step = 1;
 *                  else if maxVoltage > 50 then
 *                      voltage.upperRange = ceil(maxVoltage/10)*10
 *                      voltage.step = 10;
 *                  else
 *                      voltage.upperRange = ceil(maxVoltage/5)*5
 *                      votlage.step = 5;
 *
 *      minimum:    if minVoltage >= -MIN_VOL then
 *                      voltage.lowerRange = 0;
 *                  else if minVoltage > -5 then
 *                      voltage.lowerRange = -5;
 *                      voltage.step = 1;
 *                  else if minVolage < -50 then
 *                      voltage.lowerRange = floor(minVolage/10)*10;
 *                      voltage.step = 10;
 *                  else
 *                      voltage.lowerRange = floor(minVolage/5)*5;
 *                      voltage.step = 5;
 *
 *Measurement Current:
 *  Linear:
 *      maximum:    if maxCurrent <= MIN_CUR then
 *                      current.upperRange = 0;
 *                  else if maxCurrent < 0.1 then
 *                      current.upperRange = 0.1;
 *                      current.step = 0.01;
 *                  else if maxCurrent < 1  then
 *                      current.upperRange = 1;
 *                      current.setp = 0.1
 *                  else if maxCurrent < 3 then
 *                      current.upperRange = ceil(maxCurrent)
 *                      current.step = 0.5
 *                  else if maxCurrent >10 then
 *                      current.upperRange = ceil(maxCurrent/10)*10
 *                      current.step = 2;
 *                  else
 *                      current.upperRange = ceil(maxCurrent)
 *                      current.step=1;
 *      minimum:    if minCurrent >= -MIN_CUR then
 *                      current.lowerRange = 0;
 *                  else if minCurrent > -0.1 then
 *                      current.lowerRange = -0.1;
 *                      current.step = 0.01
 *                   else if minCurrent > -1  then
 *                      current.lowerRange = 1;
 *                      current.setp = 0.1
 *                  else if minCurrent > -3 then
 *                      current.lowerRange = floor(minCurrent)
 *                      current.step = 0.5
 *                  else if maxCurrent < -10 then
 *                      current.lowerRange = floor(minCurrent/10)*10
 *                      current.step = 2;
 *                  else
 *                      current.lowerRange = floor(minCurrent)
 *                      current.step=1;
 *  Log:
 *      maximum:    10^(ceil(log10(abs(maxCurrent))))
 *      minimum:    10^(floor(log10(abs(minCurrent))))
 *
 * LeakageCurrent:
 *  Linear:
 *      maximum:    10^(ceil(log10(abs(maxCurrent))));
 *      minimum:    10^(floor(log10(abs(minCurrent))));
 *
 *  Log:
 *      maximum:    10^(ceil(log10(abs(maxCurrent))+1));
 *      minimum:    10^(floor(log10(abs(minCurrent))-1));
 *
 * ****************************************************
 */
bool IVCurve::reScale()
{
    if (dataList.isEmpty())
        return false;

    reScaleVoltage();
    reScaleCurrent();
    reScaleLeakage();

    return true;
}

bool IVCurve::reScaleVoltage()
{
    if (dataList.isEmpty())
        return false;
    Data *data = dataList.at(0);
    int maxVoltageIndex = data->getMaximumVoltageIndex();
    int minVoltageIndex = data->getMinimumVoltageIndex();

    double maxVoltage = data->voltage.at(maxVoltageIndex);
    double minVoltage = data->voltage.at(minVoltageIndex);
    double voltageRange = maxVoltage-minVoltage;

    //Measurement Voltage:
    if (maxVoltage < MIN_VOL){
        plot->xAxis->setRangeUpper(0);
    }else if (maxVoltage < 5){
        plot->xAxis->setRangeUpper(5);
    }else if (maxVoltage > 50){
        plot->xAxis->setRangeUpper(ceil(maxVoltage/10)*10);
    }else{
        plot->xAxis->setRangeUpper(ceil(maxVoltage/5)*5);
    }

    if (minVoltage > -MIN_VOL){
        plot->xAxis->setRangeLower(0);
    }else if (minVoltage < 5){
        plot->xAxis->setRangeLower(-5);
    }else if (minVoltage > 50){
        plot->xAxis->setRangeLower(floor(minVoltage/10)*10);
    }else{
        plot->xAxis->setRangeLower(floor(minVoltage/5)*5);
    }

    if (voltageRange > 50){
        plot->xAxis->setTickStep(10);
    }else if (voltageRange <5){
        plot->xAxis->setTickStep(1);
    }else if (voltageRange <10){
        plot->xAxis->setTickStep(2);
    }else{
        plot->xAxis->setTickStep(5);
    }

    return true;
}

bool IVCurve::reScaleCurrent()
{
    if (dataList.isEmpty())
        return false;
    Data *data = dataList.at(0);
    int maxCurrentIndex = data->getMaximumCurrentIndex();
    int minCurrentIndex = data->getMinimumCurrentIndex();\
    double maxCurrent = data->current.at(maxCurrentIndex);
    double minCurrent = data->current.at(minCurrentIndex);
    double currentRange = maxCurrent - minCurrent;

    if (yAxisLinear->isChecked()){      //Linear
        if (maxCurrent < MIN_CUR){
            plot->yAxis->setRangeUpper(0);
            plot->yAxis2->setRangeUpper(0);
        }else if (maxCurrent < 0.1){
            plot->yAxis->setRangeUpper(0.1);
            plot->yAxis2->setRangeUpper(0.1);
        }else if (maxCurrent < 1){
            plot->yAxis->setRangeUpper(1);
            plot->yAxis2->setRangeUpper(1);
        }else if (maxCurrent >10){
            plot->yAxis->setRangeUpper(ceil(maxCurrent/5.0)*5);
            plot->yAxis2->setRangeUpper(ceil(maxCurrent/5.0)*5);
        }else{
            plot->yAxis->setRangeUpper(ceil(maxCurrent));
            plot->yAxis2->setRangeUpper(ceil(maxCurrent));
        }

        if (minCurrent > -MIN_CUR){
            plot->yAxis->setRangeLower(0);
            plot->yAxis2->setRangeLower(0);
        }else if (minCurrent > -0.1){
            plot->yAxis->setRangeLower(-0.1);
            plot->yAxis2->setRangeLower(-0.1);
        }else if (minCurrent > -1){
            plot->yAxis->setRangeLower(-1);
            plot->yAxis2->setRangeLower(-1);
        }else if (minCurrent < -10){
            plot->yAxis->setRangeLower(floor(minCurrent/5.0)*5);
            plot->yAxis2->setRangeLower(floor(minCurrent/5.0)*5);
        }else{
            plot->yAxis->setRangeLower(floor(minCurrent));
            plot->yAxis2->setRangeLower(floor(minCurrent));
        }

        if (currentRange <0.1){
            plot->yAxis->setTickStep(0.01);
            plot->yAxis2->setTickStep(0.01);
        }else if (currentRange < 1){
            plot->yAxis->setTickStep(0.1);
            plot->yAxis2->setTickStep(0.1);
        }else if (currentRange < 4){
            plot->yAxis->setTickStep(0.5);
            plot->yAxis2->setTickStep(0.5);
        }else if (currentRange < 10){
            plot->yAxis->setTickStep(1);
            plot->yAxis2->setTickStep(1);
        }else{
            plot->yAxis->setTickStep(2);
            plot->yAxis2->setTickStep(2);
        }

    }else{      //Log
        plot->yAxis->setRangeUpper(pow(double(10),ceil(log10(fabs(maxCurrent)))));
        plot->yAxis2->setRangeUpper(pow(double(10),ceil(log10(fabs(maxCurrent)))));

        plot->yAxis->setRangeLower(pow(double(10),floor(log10(fabs(minCurrent)))));
        plot->yAxis2->setRangeLower(pow(double(10),floor(log10(fabs(minCurrent)))));

        if (fabs(maxCurrent)/fabs(minCurrent)>1e8){
            plot->yAxis->setScaleLogBase(100);
            plot->yAxis2->setScaleLogBase(100);
        }else{
            plot->yAxis->setScaleLogBase(10);
            plot->yAxis->setScaleLogBase(10);
        }
    }

    return true;

}

bool IVCurve::reScaleLeakage()
{
    if (dataList.isEmpty())
        return false;
    Data *data = dataList.at(0);
    int maxLeakageIndex = data->getMaximumLeakageIndex();
    int minLeakageIndex = data->getMinimumLeakageIndex();
    double maxLeakage = data->leakage.at(maxLeakageIndex);
    double minLeakage = data->leakage.at(minLeakageIndex);

    if (xAxis2Linear->isChecked()){
        plot->xAxis2->setRangeUpper(pow(double(10),ceil(log10(fabs(maxLeakage)))));
        plot->xAxis2->setRangeLower(0);
        plot->xAxis2->setTickStep(pow(double(10),ceil(log10(fabs(minLeakage)))-1));
    }else{
        plot->xAxis2->setRangeUpper(pow(double(10),ceil(log10(fabs(maxLeakage)))+1));
        plot->xAxis2->setRangeLower(pow(double(10),floor(log10(fabs(minLeakage)))-1));

        if (fabs(maxLeakage)/fabs(minLeakage)>1e4){
            plot->xAxis2->setScaleLogBase(100);
        }else{
            plot->xAxis2->setScaleLogBase(10);
        }
    }

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

void IVCurve::setXAxis2ScaleType(int id)
{
    Q_UNUSED(id);
    if (xAxis2Linear->isChecked()){
        plot->xAxis2->setScaleType(QCPAxis::stLinear);
    }else{
        plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
    }
    reScaleLeakage();
    replot();
}

void IVCurve::setYAxisScaleType(int id)
{
    Q_UNUSED(id);
    if (yAxisLinear->isChecked()){
        plot->yAxis->setScaleType(QCPAxis::stLinear);
        plot->yAxis2->setScaleType(QCPAxis::stLinear);
    }else{
        plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        plot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
    }
    reScaleCurrent();
    replot();
}

void IVCurve::setDisplayable(int id)
{
    Q_UNUSED(id);
    if(plot->plottableCount() == 0)
        return;
    if(measurement->isChecked()){
        plot->plottable(0)->setVisible(true);
    }else{
        plot->plottable(0)->setVisible(false);
    }
    if(leakage->isChecked()){
        plot->plottable(1)->setVisible(true);
    }else{
        plot->plottable(1)->setVisible(false);
    }
    if(legend->isChecked()){
        plot->legend->setVisible(true);
    }else{
        plot->legend->setVisible(false);
    }
    replot();
}
