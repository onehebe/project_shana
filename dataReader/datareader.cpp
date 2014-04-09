#include "datareader.h"


DataReader::DataReader()
{
    dataFileFormat = "sbd";
    fileName = "E:/ESD/CB6040/5-1-3/Result/5-1-3_hanwa_esd_hanwa_esd.sbd";


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
        return true;
    }
    return false;
}

QMap<int, double, double, double> *DataReader::getData()
{

}
