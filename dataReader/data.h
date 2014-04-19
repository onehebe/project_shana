#ifndef DATA_H
#define DATA_H
#include "datareader_global.h"
#include <QVector>
#include <QString>

class DATAREADERSHARED_EXPORT Data
{
public:
    Data();

    QString name;
    QVector<double> count;
    QVector<double> zap;
    QVector<double> voltage;
    QVector<double> current;
    QVector<double> leakage;

    int getMaximumZapIndex();
    int getMinimumZapIndex();
    int getMaximumVoltageIndex();
    int getMinimumVoltageIndex();
    int getMaximumCurrentIndex();
    int getMinimumCurrentIndex();
    int getMaximumLeakageIndex();
    int getMinimumLeakageIndex();
};

#endif // DATA_H
