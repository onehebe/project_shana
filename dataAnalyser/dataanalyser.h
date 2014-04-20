#ifndef DATAANALYSER_H
#define DATAANALYSER_H

#include <QWidget>
#include <Qprinter>
#include "ivcurve.h"
#include "data.h"
#include "datareader.h"

#define NONE        0
#define RESISTOR    1
#define NONSNAPBACK 2
#define SNAPBACK    3
#define UNDEFINED   4

#define FST_REF_RATIO 1.5
#define FST_TRIG_RATIO 1.8
#define SND_TRIG_RATIO 1.6
#define SND_TRIG_TOL    5

class dataAnalyser : public QWidget
{
    Q_OBJECT
public:
    explicit dataAnalyser(QWidget *parent = 0);

    QMenuBar *menuBar;
    QStatusBar *statusBar;

    QGridLayout *layout;
    QVBoxLayout *infoLayout;

    IVCurve *curveWidget;

    Data *data;
    DataReader *reader;

    QGroupBox *deviceInfo;
    QGroupBox *extractInfo;

    QLabel *nameLabel;
    QLabel *typeLabel;
    QLabel *trig1CurrentLabel;
    QLabel *trig1VoltageLabel;
    QLabel *trig2VoltageLabel;
    QLabel *trig2CurrentLabel;
    QLabel *holdingLabel;

    QLineEdit *nameText;
    QLineEdit *typeText;
    QLineEdit *trig1CurrentText;
    QLineEdit *trig1VoltageText;
    QLineEdit *trig2CurrentText;
    QLineEdit *trig2VoltageText;
    QLineEdit *holdingText;

    void initMenuBar();
    void initStatusBar();

    bool isConfigLoaded;
    bool setFile(QString &file);
    bool setConfig(QString &file);
    bool analyze(QString &file);
    bool plot();
    bool extract(Data *srcData);

    void createPDF(QString &path);

signals:

public slots:
    void openData();
    void savePDF();

private:
    QString currentPath;

    int type;
    int countTrig1;
    int countTrig2;
    double holdingVoltage;
};

#endif // DATAANALYSER_H
