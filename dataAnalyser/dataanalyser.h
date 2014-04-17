#ifndef DATAANALYSER_H
#define DATAANALYSER_H

#include <QWidget>
#include "ivcurve.h"
#include "data.h"
#include "datareader.h"

#include <QDebug>

class dataAnalyser : public QWidget
{
    Q_OBJECT
public:
    explicit dataAnalyser(QWidget *parent = 0);

    QGridLayout *layout;
    QVBoxLayout *infoLayout;

    IVCurve *curveWidget;

    Data *data;
    DataReader *reader;

    QLabel *nameLabel;
    QLabel *typeLabel;
    QLabel *trig1Label;
    QLabel *trig2Label;
    QLabel *holdingLabel;

    QLineEdit *nameText;
    QLineEdit *typeText;
    QLineEdit *trig1Text;
    QLineEdit *trig2Text;
    QLineEdit *holdingText;

    bool isConfigSetted;
    bool setFile(QString &file);
    bool setConfig(QString &file);
    bool analyze(QString &file);
    bool plot();
signals:

public slots:

};

#endif // DATAANALYSER_H
