#include "dataanalyser.h"

dataAnalyser::dataAnalyser(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout(this);
    infoLayout = new QVBoxLayout(this);
    curveWidget = new IVCurve(this);

    deviceInfo = new QGroupBox(tr("Device Information:"));
    extractInfo = new QGroupBox(tr("Extaction:"));
    QVBoxLayout *dInfoLyt = new QVBoxLayout();
    QVBoxLayout *exInfoLyt = new QVBoxLayout();

    nameLabel = new QLabel("Name:",this);
    typeLabel = new QLabel("Type:",this);
    trig1CurrentLabel = new QLabel("1st Trig Current:",this);
    trig1VoltageLabel = new QLabel("1st Trig Voltage:",this);
    trig2CurrentLabel = new QLabel("2nd Trig Current:",this);
    trig2VoltageLabel = new QLabel("2nd Trig Voltage:",this);
    holdingLabel = new QLabel("Holding:",this);

    nameText = new QLineEdit(this);
    typeText = new QLineEdit(this);
    trig1CurrentText = new QLineEdit(this);
    trig1VoltageText = new QLineEdit(this);
    trig2CurrentText = new QLineEdit(this);
    trig2VoltageText = new QLineEdit(this);
    holdingText = new QLineEdit(this);

    nameText->setFixedWidth(150);
    typeText->setFixedWidth(150);
    trig1CurrentText->setFixedWidth(150);
    trig1VoltageText->setFixedWidth(150);
    trig2CurrentText->setFixedWidth(150);
    trig2VoltageText->setFixedWidth(150);
    holdingText->setFixedWidth(150);
    deviceInfo->setFixedWidth(180);
    deviceInfo->setFixedHeight(100);
    extractInfo->setFixedWidth(180);
    extractInfo->setFixedHeight(300);

    dInfoLyt->addWidget(nameLabel);
    dInfoLyt->addWidget(nameText);
    exInfoLyt->addWidget(typeLabel);
    exInfoLyt->addWidget(typeText);
    exInfoLyt->addWidget(trig1CurrentLabel);
    exInfoLyt->addWidget(trig1CurrentText);
    exInfoLyt->addWidget(trig1VoltageLabel);
    exInfoLyt->addWidget(trig1VoltageText);
    exInfoLyt->addWidget(trig2CurrentLabel);
    exInfoLyt->addWidget(trig2CurrentText);
    exInfoLyt->addWidget(trig2VoltageLabel);
    exInfoLyt->addWidget(trig2VoltageText);
    exInfoLyt->addWidget(holdingLabel);
    exInfoLyt->addWidget(holdingText);

    deviceInfo->setLayout(dInfoLyt);
    extractInfo->setLayout(exInfoLyt);

    infoLayout->addWidget(deviceInfo);
    infoLayout->addWidget(extractInfo);
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

    initMenuBar();

    currentPath = "./";
}

void dataAnalyser::initMenuBar()
{
    menuBar = new QMenuBar();

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));

    QAction *openAction = new QAction(tr("&Open"),this);
    QAction *saveAction = new QAction(tr("&Save"),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(openData()));

    QAction *configActon = new QAction(tr("&Configure"),this);

    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);

    editMenu->addAction(configActon);
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
        QMessageBox noFile(QMessageBox::Warning,tr("Warning"),tr("No File is selected."),QMessageBox::Ok);
        noFile.exec();
        return false;
    }
    if(!reader->readData()){
        QMessageBox readFail(QMessageBox::Warning,tr("Warning"),tr("Unsupported Data File.\nPlease check your config file."),QMessageBox::Ok);
        readFail.exec();
        return false;
    }
    data = reader->getData();
    return plot();
}

bool dataAnalyser::plot()
{
    return curveWidget->addPlot(*data);
}

void dataAnalyser::openData()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open File"),currentPath);
    currentPath = QDir(file).path();
    if (!file.isEmpty()){
        analyze(file);
    }
}




