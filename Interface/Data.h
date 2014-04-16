#ifndef DATA_H
#define DATA_H

#include <QVector>
#include "interface_global.h"

class INTERFACESHARED_EXPORT data{
    template <typename T>
    virtual QVector<T>* getData();
};

#endif // DATA_H
