#ifndef DATA_H
#define DATA_H
#include "datareader_global.h"
#include <QVector>

class DATAREADERSHARED_EXPORT Data
{
    Data();

public:
    QVector<int> count;
    QVector<double> zap;
    QVector<double> voltage;
    QVector<double> current;
    QVector<double> leakage;
};

#endif // DATA_H
