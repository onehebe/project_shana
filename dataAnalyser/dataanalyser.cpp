#include "dataanalyser.h"

dataAnalyser::dataAnalyser(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout(this);
    infoLayout = new QVBoxLayout(this);
    curveWidget = new IVCurve(this);

    nameLabel = new QLabel("Name:",this);
    typeLabel = new QLabel("Type:",this);
    trig1Label = new QLabel("Trigger 1:",this);
    trig2Label = new QLabel("Trigger 2:",this);
    holdingLabel = new QLabel("Holding:",this);

    nameText = new QLineEdit(this);
    typeText = new QLineEdit(this);
    trig1Text = new QLineEdit(this);
    trig2Text = new QLineEdit(this);
    holdingText = new QLineEdit(this);

    nameText->setMaximumWidth(200);
    typeText->setMaximumWidth(200);
    trig1Text->setMaximumWidth(200);
    trig2Text->setMaximumWidth(200);
    holdingText->setMaximumWidth(200);

    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(nameText);
    infoLayout->addWidget(typeLabel);
    infoLayout->addWidget(typeText);
    infoLayout->addWidget(trig1Label);
    infoLayout->addWidget(trig1Text);
    infoLayout->addWidget(trig2Label);
    infoLayout->addWidget(trig2Text);
    infoLayout->addWidget(holdingLabel);
    infoLayout->addWidget(holdingText);
    infoLayout->addStretch();

    layout->addLayout(infoLayout,0,0,-1,1);
    layout->addWidget(curveWidget,0,1,-1,-1);
    layout->setColumnMinimumWidth(0,100);
    layout->setColumnMinimumWidth(1,800);

    this->setLayout(layout);

    reader = new DataReader();

    isConfigSetted = false;

    if (QFile::exists("F:/develop/qt/project_shana/dataAnalyser/config/interpreter.js")){
        isConfigSetted = reader->setScript("F:/develop/qt/project_shana/dataAnalyser/config/interpreter.js");
    }
}

bool dataAnalyser::setFile(QString &file)
{
    if (QFile::exists(file)){
        return reader->setFile(file);
    }
    return false;
}

bool dataAnalyser::setConfig(QString &file)
{
    if (QFile::exists(file)){
        isConfigSetted = reader->setScript(file);
        return isConfigSetted;
    }
    return false;
}

bool dataAnalyser::analyze(QString &file)
{
    if (!isConfigSetted){
        return false;
    }
    if (!setFile(file)){
        return false;
    }
    if(!reader->readData()){
        return false;
    }
    data = reader->getData();
    return plot();
}

bool dataAnalyser::plot()
{
    return curveWidget->addPlot(*data);
}




