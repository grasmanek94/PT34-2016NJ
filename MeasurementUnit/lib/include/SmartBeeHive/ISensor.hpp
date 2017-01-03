#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_

#include <SmartBeeHive/IMeasurementSink.hpp>

class ISensor {
public:
    ISensor(IMeasurementSink &sink, int targetInterval, char* keyword) { }
    virtual ~ISensor() { }

    virtual void run() = 0;
    virtual char* getKeyword() = 0;
    virtual void setKeyword(char* keyword) = 0;
};

#endif // ISENSOR_HPP_
