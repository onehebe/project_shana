#include "dataanalyser.h"

dataAnalyser::dataAnalyser(QWidget *parent) :
    QWidget(parent)
{
    type = NONE;
    countTrig1 = -1;
    countTrig2 = -1;
    holdingVoltage = 0;

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

    isConfigLoaded = false;

    if (QFile::exists("script/config/default/interpreter.js")){
        QFile *scriptFile = new QFile("script/config/default/interpreter.js");
        scriptFile->open(QIODevice::ReadOnly);
        QTextStream scriptStream(scriptFile);
        isConfigLoaded = reader->setScriptContext(scriptStream.readAll());
        scriptFile->close();
    }else{
        isConfigLoaded = false;
        QMessageBox noScript(QMessageBox::Warning,tr("Warning"),tr("Configurature loading failed."),QMessageBox::Ok);
        noScript.exec();
    }
    initMenuBar();
    initStatusBar();


    currentPath = "./";
}

void dataAnalyser::initMenuBar()
{
    menuBar = new QMenuBar();

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    QMenu *exportMenu = menuBar->addMenu(tr("E&xport"));

    QAction *openAction = new QAction(tr("&Open"),this);
    QAction *saveAction = new QAction(tr("&Save"),this);
    QAction *exportPDFAction = new QAction(tr("&Export to PDF"),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(openData()));
    connect(exportPDFAction,SIGNAL(triggered()),this,SLOT(savePDF()));

    QAction *configActon = new QAction(tr("&Configure"),this);

    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);

    editMenu->addAction(configActon);

    exportMenu->addAction(exportPDFAction);
}

void dataAnalyser::initStatusBar()
{
    statusBar = new QStatusBar();
    statusBar->showMessage(tr("Interpreter: ").append((isConfigLoaded)? "loaded" : "loading failed."));
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
        isConfigLoaded = reader->setScript(file);
        return isConfigLoaded;
    }
    return false;
}

bool dataAnalyser::analyze(QString &file)
{
    if (!isConfigLoaded){
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

    if (!extract(data))
        return false;
    statusBar->showMessage(tr("Hello, yi shen. ").append(data->name));
    return plot();
}

bool dataAnalyser::plot()
{
    if (type == NONE){
        typeText->setText(tr("None"));
    }else{
        switch(type){
        case RESISTOR:
             typeText->setText(tr("Resistor"));
             break;
        case NONSNAPBACK:
             typeText->setText(tr("Diode"));
             break;
        case SNAPBACK:
             typeText->setText(tr("With SNAPBACK"));
             break;
        case UNDEFINED:
             typeText->setText(tr("Undefined type"));
             break;
        }
    }

    if (countTrig1 == -1){
        trig1CurrentText->setText(tr("None"));
        trig1VoltageText->setText(tr("None"));
    }else{
        trig1CurrentText->setText(QString::number(data->current.at(countTrig1)));
        trig1VoltageText->setText(QString::number(data->voltage.at(countTrig1)));
    }

    if (countTrig2 == -1){
        trig2CurrentText->setText(tr("None"));
        trig2VoltageText->setText(tr("None"));
    }else{
        trig2CurrentText->setText(QString::number(data->current.at(countTrig2)));
        trig2VoltageText->setText(QString::number(data->voltage.at(countTrig2)));
    }

    if (holdingVoltage == 0){
        holdingText->setText(tr("None"));
    }else{
        holdingText->setText(QString::number(holdingVoltage));
    }

    nameText->setText(data->name);

    return curveWidget->addPlot(*data);
}

bool dataAnalyser::extract(Data *srcData)
{
    int totalNum = srcData->count.size()-1;
    int index = 0;
    int firstRef=0;
    int secondRef=0;
    if (totalNum < 3){
        type = UNDEFINED;
        countTrig1 = -1;
        countTrig2 = -1;
        holdingVoltage = 0;
        return false;
    }
    //resistor
    if (srcData->zap.at(floor(totalNum/3.0))*srcData->zap.at(floor(2*totalNum/3.0))*srcData->zap.at(floor(3*totalNum/3.0)) == 0){
        type = UNDEFINED;
        countTrig1 = -1;
        countTrig2 = -1;
        holdingVoltage = 0;
        return false;
    }

    double gradient1of3 = srcData->voltage.at(floor(totalNum/3.0))/srcData->zap.at(floor(totalNum/3.0));
    double gradient2of3 = srcData->voltage.at(floor(2*totalNum/3.0))/srcData->zap.at(floor(2*totalNum/3.0));
    double gradient3of3 = srcData->voltage.at(totalNum)/srcData->zap.at(totalNum);
    if (0.9<(gradient1of3/gradient3of3) && (gradient1of3/gradient3of3)<1.1 && 0.9<(gradient2of3/gradient3of3) && (gradient2of3/gradient3of3)<1.1){
        type = RESISTOR;
        countTrig1 = -1;
        countTrig2 = -1;
        holdingVoltage = 0;
        return true;
    }

    //find first ref point
    for(index=1;index<=totalNum;index++){
        if (srcData->voltage.at(index)*srcData->zap.at(index) > 0){
            if ((srcData->voltage.at(index)/srcData->zap.at(index)) < FST_REF_RATIO){
                firstRef = index;
                break;
            }
        }
    }

    if(index > totalNum || firstRef == 1){
        type = RESISTOR;
        countTrig1 = -1;
        countTrig2 = -1;
        holdingVoltage = 0;
        return true;
    }

    //find 1st trigger point
    for(index = firstRef;index>0;index--){
        if (srcData->zap.at(index)*srcData->voltage.at(index) > 0){
            if ((srcData->voltage.at(index)/srcData->zap.at(index)) > FST_TRIG_RATIO){
                countTrig1 = index;
                break;
            }
        }
    }

    int tol = 0;
    secondRef = firstRef;
    //find 2st ref point
    for(index = firstRef+1;(index<=totalNum)&&(tol<SND_TRIG_TOL);index++){
        if (srcData->leakage.at(index)*srcData->zap.at(index) <= 0){
            double tempVol1 = srcData->voltage.at(secondRef)-srcData->voltage.at(secondRef-1);
            double tempVol2 = srcData->voltage.at(index)-srcData->voltage.at(secondRef);
            if (tempVol1*tempVol2 == 0){
                secondRef=index+1;
                index++;
                tol=0;
                continue;
            }
            if ((fabs(tempVol2/tempVol1) >5)){
                tol=SND_TRIG_TOL;
                break;
            }else{
                secondRef=index+1;
                index++;
                tol = 0;
                continue;
            }
        }
        if (fabs((srcData->leakage.at(index)/srcData->leakage.at(secondRef))) > SND_TRIG_RATIO || fabs((srcData->leakage.at(secondRef)/srcData->leakage.at(index)) > SND_TRIG_RATIO)){
           tol++;
        }else{
            secondRef=index;
            tol=0;
        }
    }
    //determine 2st trigger point
    if(tol == SND_TRIG_TOL)
        countTrig2 = secondRef;
    else if(tol!=0 && index>totalNum)
        countTrig2 = secondRef;
    else
        countTrig2 = -1;

    //determin holding
    int holdingPoint = firstRef+1;
    holdingVoltage = srcData->voltage.at(holdingPoint);

    for(index=holdingPoint; index<secondRef; index++){
        if (srcData->voltage.at(index) < holdingVoltage){
            holdingVoltage = srcData->voltage.at(index);
            holdingPoint = index;
        }
    }

    //detmermin type
    if ((srcData->voltage.at(firstRef) < srcData->voltage.at(countTrig1)) && (srcData->voltage.at(holdingPoint) < srcData->voltage.at(countTrig1)))
        type = SNAPBACK;
    else
        type = NONSNAPBACK;

    return true;
}

void dataAnalyser::createPDF(QString &path)
{
    if (!path.endsWith(".pdf",Qt::CaseInsensitive))
        path.append(".pdf");
    QPrinter pdfPrinter(QPrinter::HighResolution);
    pdfPrinter.setPageSize(QPrinter::A4);
    pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
    pdfPrinter.setOutputFileName(path);

    curveWidget->plot->savePng("temp.png",800,600,2.0);

    QString html;
    html += "<h2 align='center'>TLP Data</h2>";
    html += "<h4>Device Name</h4><br>";
    html += nameText->text() + "<br>";
    html += "<h4>Information:</h4><br>";
    html += "Type: " + typeText->text() + "<br>";
    html += "<table align=\"left\" border=\"2\" width=\"200\">";
    if (trig1CurrentText->text() != "None"){
        html += "<tr><td>I_t1</td><td>"+trig1CurrentText->text()+"</td></tr>";
        html += "<tr><td>V_t1</td><td>"+trig1VoltageText->text()+"</td></tr>";
    }
    if (trig2CurrentText->text() != "None"){
        html += "<tr><td>I_t2</td><td>"+trig2CurrentText->text()+"</td></tr>";
        html += "<tr><td>V_t2</td><td>"+trig2VoltageText->text()+"</td></tr>";
    }
    if (holdingText->text() != "None"){
        html += "<tr><td>V_h</td><td>"+holdingText->text()+"</td></tr>";
    }
    html += "</table><br>";

    html += "<h4>Figure:</h4><br>";
    html += "<img align=\"middle\" src=\"temp.png\" width=\"600\" height=\"450\" /><br>";

    QTextDocument text;
    text.setHtml(html);
    text.print(&pdfPrinter);
    text.end();
}

void dataAnalyser::openData()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open File"),currentPath);
    currentPath = QDir(file).path();
    if (!file.isEmpty()){
        analyze(file);
    }
}

void dataAnalyser::savePDF()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Export PDF"),QString(),"*.pdf");
    createPDF(path);
}


