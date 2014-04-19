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

    QMenuBar *menuBar;

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

    bool isConfigSetted;
    bool setFile(QString &file);
    bool setConfig(QString &file);
    bool analyze(QString &file);
    bool plot();

signals:

public slots:
    void openData();

private:
    QString currentPath;
};

#endif // DATAANALYSER_H
