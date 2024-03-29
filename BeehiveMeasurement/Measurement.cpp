#include "Measurement.hpp"
#include <stddef.h>

Measurement::Measurement(double data, char* type, int id)
    :_data(data), _type(type), _id(id)
{

}

Measurement::~Measurement()
{

}

double Measurement::getData() const
{
    return _data;
}

void Measurement::setData(double data)
{
    _data = data;
}

char* Measurement::getType() const {
    return _type;
}

void Measurement::setType(char* type) {
    _type = type;
}

int Measurement::getId() const {
    return _id;
}
void Measurement::setId(int id) {
    _id = id;
}
