#ifndef DATAREADER_H
#define DATAREADER_H

#include "datareader_global.h"
#include <QDir>
#include <QMap>
#include <QFile>
#include <QScriptEngine>
#include <QScriptValue>

class DATAREADERSHARED_EXPORT DataReader
{

public:
    DataReader();

    bool setFile(QString path);
    bool setScript(QString path);

    QMap<int,double,double,double>* getData();
    QList<int>* getCountList();
    QList<double>* getZapList();
    QList<double>* getCurrentList();
    QList<double>* getVoltageList();
    QList<double>* getLeakageList();

protected:
    static QDir configDir;
    static QDir dataDir;

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
