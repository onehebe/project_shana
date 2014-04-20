#include "datareader.h"


DataReader::DataReader()
{
    data = new Data();
}

bool DataReader::setFile(QString path)
{
    if(QFile::exists(path)){
        filePath = path;
        file.setFileName(path);
        return true;
    }
    return false;
}

bool DataReader::setScript(QString path)
{
    if(QFile::exists(path)){
        scriptPath = path;
        script.setFileName(path);
        script.open(QIODevice::ReadWrite);
        QTextStream stream(&script);
        scriptContext = stream.readAll();
        script.close();
        return true;
    }
    return false;
}

bool DataReader::setScript(QFile *scriptFile)
{
    if (scriptFile){
        scriptFile->open(QIODevice::ReadOnly);
        QTextStream stream(&script);
        scriptContext = stream.readAll();
        scriptFile->close();
        return true;
    }
    return false;
}

bool DataReader::setScriptContext(QString scriptcontex)
{
    if (!scriptcontex.isEmpty()){
        scriptContext = scriptcontex;
        return true;
    }
    return false;
}

bool DataReader::readData()
{
    if (data)
        delete data;
    data = new Data();
    if (file.open(QIODevice::ReadOnly)){
        QTextStream dataStream(&file);
        QString dataString = dataStream.readAll();
        file.close();

        if (dataString.isEmpty())
            return false;

        QScriptValue dataLines(&interpreter,dataString);

        countValue = interpreter.newArray();
        zapValue = interpreter.newArray();
        voltageValue = interpreter.newArray();
        currentValue = interpreter.newArray();
        leakageValue = interpreter.newArray();

        interpreter.globalObject().setProperty("text",dataLines);

        interpreter.globalObject().setProperty("count",countValue);
        interpreter.globalObject().setProperty("zap",zapValue);
        interpreter.globalObject().setProperty("voltage",voltageValue);
        interpreter.globalObject().setProperty("current",currentValue);
        interpreter.globalObject().setProperty("leakage",leakageValue);

        interpreter.evaluate(scriptContext);

        QScriptValue result =  interpreter.globalObject().property("status");

        if (!result.toBool())
            return false;

        QList<QVariant> count,zap,voltage,current,leakage;

        count = countValue.toVariant().toList();
        zap = zapValue.toVariant().toList();
        voltage = voltageValue.toVariant().toList();
        current = currentValue.toVariant().toList();
        leakage = leakageValue.toVariant().toList();

        int maxCount = count.size()-1;
        for (int i=0;i<maxCount;i++){
            data->count.append(count.at(i).toDouble());
            data->zap.append(zap.at(i).toDouble());
            data->current.append(current.at(i).toDouble());
            data->voltage.append(voltage.at(i).toDouble());
            data->leakage.append(leakage.at(i).toDouble());
        }
        QFileInfo finfo(file);
        data->name = finfo.baseName();

        return true;
    }
    return false;
}

Data *DataReader::getData()
{
    return data;
}

QVector<double> *DataReader::getCountVector()
{
    if (data)
        return &(data->count);
    return nullptr;
}

QVector<double> *DataReader::getZapVector()
{
    if (data)
        return &(data->zap);
    return nullptr;
}

QVector<double> *DataReader::getCurrentVector()
{
    if (data)
        return &(data->current);
    return nullptr;
}

QVector<double> *DataReader::getVoltageVector()
{
    if (data)
        return &(data->voltage);
    return nullptr;
}

QVector<double> *DataReader::getLeakageVector()
{
    if (data)
        return &(data->leakage);
    return nullptr;
}
