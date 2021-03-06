#ifndef DATAREADER_H
#define DATAREADER_H

#include "datareader_global.h"
#include <QDir>
#include <QMap>
#include <QFile>
#include <QScriptEngine>
#include <QScriptValue>
#include <QTextStream>
#include "data.h"

class DATAREADERSHARED_EXPORT DataReader
{

public:
    DataReader();

    bool setFile(QString path);
    bool setScript(QString path);
    bool setScript(QFile *scriptFile);
    bool setScriptContext(QString scriptcontex);
    bool readData();

    Data* getData();
    QVector<double> *getCountVector();
    QVector<double>* getZapVector();
    QVector<double>* getCurrentVector();
    QVector<double>* getVoltageVector();
    QVector<double>* getLeakageVector();

protected:
    static QDir configDir;
    static QDir dataDir;

    Data* data;

    QString scriptContext;

    QScriptEngine interpreter;

    QScriptValue countValue;
    QScriptValue zapValue;
    QScriptValue currentValue;
    QScriptValue voltageValue;
    QScriptValue leakageValue;

    QFile file;
    QFile script;

    QString dataFileFormat;
    QString timeFormat;
    QString titleFormat;
    QString deviceName;

    QString fileName;
    QString filePath;
    QString scriptPath;
};

#endif // DATAREADER_H
