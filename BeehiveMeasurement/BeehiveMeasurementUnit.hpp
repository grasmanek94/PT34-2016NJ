#ifndef BEEHIVE_MEASUREMENT_UNIT_HPP_
#define BEEHIVE_MEASUREMENT_UNIT_HPP_

#include "ISensor.hpp"
#include <Arduino.h>

class BeehiveMeasurementUnit {
public:
    BeehiveMeasurementUnit(size_t nrSensors, ISensor** _sensor);
    virtual ~BeehiveMeasurementUnit();

    void init();
    void run();
    void stop();
    bool status();

private:
    size_t _nrSensors;
    ISensor** _sensors;
    bool _running;
};

#endif // BEEHIVE_MEASUREMENT_UNIT_HPP_
