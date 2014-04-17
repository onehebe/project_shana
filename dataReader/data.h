#ifndef DATA_H
#define DATA_H
#include "datareader_global.h"
#include <QVector>

class DATAREADERSHARED_EXPORT Data
{
public:
    Data();

    QVector<double> count;
    QVector<double> zap;
    QVector<double> voltage;
    QVector<double> current;
    QVector<double> leakage;

    int getMaximumVoltageIndex();
    int getMinimumVoltageIndex();
    int getMaximumCurrentIndex();
    int getMinimumCurrentIndex();
    int getMaximumLeakageIndex();
    int getMinimumLeakageIndex();
};

#endif // DATA_H
