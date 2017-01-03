#include <SmartBeeHive/Measurement.hpp>
#include <stddef.h>

Measurement::Measurement(int data, char *sensorKeyword)
    :_data(data), _sensorKeyword(sensorKeyword)
{

}

Measurement::~Measurement()
{

}

int Measurement::getData() const
{
    return _data;
}

void Measurement::setData(int data)
{
    _data = data;
}

char *Measurement::getSensorKeyword() const
{
    return _sensorKeyword;
}

void Measurement::setSensorKeyword(char *sensorKeyword)
{
    if(sensorKeyword != NULL){
        _sensorKeyword = sensorKeyword;
    }
}
