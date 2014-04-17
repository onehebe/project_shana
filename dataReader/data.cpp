#include <data.h>


Data::Data()
{
}

int Data::getMaximumVoltageIndex()
{
    if (voltage.isEmpty())
        return 0;
    double maximum = voltage.first();
    int index = 0;
    for(auto it=voltage.begin();it!=voltage.end();++it){
        if (maximum<(*it)){
            maximum = (*it);
            index = voltage.indexOf(maximum);
        }
    }
    return index;
}

int Data::getMinimumVoltageIndex()
{
    if (voltage.isEmpty())
        return 0;
    double minimum = voltage.first();
    int index = 0;
    for(auto it=voltage.begin();it!=voltage.end();++it){
        if (minimum > (*it)){
            minimum = (*it);
            index = voltage.indexOf(minimum);
        }
    }
    return index;
}

int Data::getMaximumCurrentIndex()
{
    if (current.isEmpty())
        return 0;
    double maximum = current.first();
    int index = 0;
    for(auto it=current.begin();it!=current.end();++it){
        if (maximum<(*it)){
            maximum = (*it);
            index = current.indexOf(maximum);
        }
    }
    return index;
}

int Data::getMinimumCurrentIndex()
{
    if (current.isEmpty())
        return 0;
    double minimum = current.first();
    int index = 0;
    for(auto it=current.begin();it!=current.end();++it){
        if (minimum > (*it)){
            minimum = (*it);
            index = current.indexOf(minimum);
        }
    }
    return index;
}

int Data::getMaximumLeakageIndex()
{
    if (leakage.isEmpty())
        return 0;
    double maximum = leakage.first();
    int index = 0;
    for(auto it=leakage.begin();it!=leakage.end();++it){
        if (maximum<(*it)){
            maximum = (*it);
            index = leakage.indexOf(maximum);
        }
    }
    return index;
}

int Data::getMinimumLeakageIndex()
{
    if (leakage.isEmpty())
        return 0;
    double minimum = leakage.first();
    int index = 0;
    for(auto it=leakage.begin();it!=leakage.end();++it){
        if (minimum > (*it)){
            minimum = (*it);
            index = leakage.indexOf(minimum);
        }
    }
    return index;
}
