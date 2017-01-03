#ifndef IMEASUREMENTSINK_HPP_
#define IMEASUREMENTSINK_HPP_

#include <SmartBeeHive/Measurement.hpp>

class IMeasurementSink {
public:
    IMeasurementSink() { }
    virtual ~IMeasurementSink() { }

    virtual void sendMeasurement(Measurement measurement) = 0;
};

#endif // IMEASUREMENTSINK_HPP_
