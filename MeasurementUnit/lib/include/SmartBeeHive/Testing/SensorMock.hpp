#ifndef SENSOR_MOCK_HPP_
#define SENSOR_MOCK_HPP_

#include "gmock/gmock.h"
#include <SmartBeeHive/ISensor.hpp>
#include <SmartBeeHive/Testing/MeasurementSinkMock.hpp>

namespace Testing {

class SensorMock : public ISensor {
public:
    SensorMock(MeasurementSinkMock& sink, int targetInterval, char* key) : ISensor(sink, targetInterval, key) { }

    MOCK_METHOD0(run, void());
    MOCK_METHOD0(getKeyword, char*());
    MOCK_METHOD1(setKeyword, void(char* keyword));
};

} // namespace Testing

#endif // SENSOR_MOCK_HPP_
