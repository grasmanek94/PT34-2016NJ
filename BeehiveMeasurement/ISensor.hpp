#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_

#include "IMeasurementSink.hpp"

class ISensor {
public:
    ISensor(IMeasurementSink &sink, int targetInterval, char* type, int index) { }
    virtual ~ISensor() { }

    virtual void run() = 0;
    virtual char* getType() = 0;
    virtual void setType(char* keyword) = 0;

    virtual int getIndex() = 0;
    virtual void setIndex(int index) = 0;
};

#endif // ISENSOR_HPP_
