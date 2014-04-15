#include "datareader.h"


DataReader::DataReader()
{
    operand = interpreter.newObject();
    interpreter.globalObject().setProperty("line",operand);
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

Data *DataReader::getData()
{
    Data *dataSet = new Data();
    if (file.open(QIODevice::ReadOnly)){
        QTextStream dataStream(&file);
        QString data = dataStream.readAll();

        if (data.isEmpty())
            return nullptr;

        QScriptValue dataLines(&interpreter,data);

        countValue = interpreter.newArray();
        zapValue = interpreter.newArray();
        voltageValue = interpreter.newArray();
        currentValue = interpreter.newArray();
        leakageValue = interpreter.newArray();

        interpreter.globalObject().setProperty("text",dataLines);

        interpreter.globalObject().setProperty("count",countValue);
        interpreter.globalObject().setProperty("zap",countValue);
        interpreter.globalObject().setProperty("voltage",voltageValue);
        interpreter.globalObject().setProperty("current",currentValue);
        interpreter.globalObject().setProperty("leakage",leakageValue);

        QScriptValue result = engine.evaluate(scriptContext);

        if (!result.isBool())
            return nullptr;
        if (!result.toBool())
            return nullptr;

        QList<QVariant> count,zap,voltage,current,leakage;

        count = countValue.toVariant().toList();
        zap = zapValue.toVariant().toList();
        voltage = voltageValue.toVariant().toList();
        current = currentValue.toVariant().toList();
        leakage = leakageValue.toVariant().toList();

        for (int i=count.size()-1;i>=0;i--){
            dataSet->count.append(countValue.at(i).toInt());
            dataSet->zap.append(zapValue.at(i).toDouble());
            dataSet->current.append(currentValue.at(i).toDouble());
            dataSet->voltage.append(voltageValue.at(i).toDouble());
            dataSet->leakage.append(leakageValue.at(i).toDouble());
        }

        return dataSet;
    }
    return nullptr;
}
