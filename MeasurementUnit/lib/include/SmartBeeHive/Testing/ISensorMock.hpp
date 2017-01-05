#ifndef ISENSOR_MOCK_HPP_
#define ISENSOR_MOCK_HPP_

#include "gmock/gmock.h"
#include <SmartBeeHive/ISensor.hpp>
#include <SmartBeeHive/Testing/IMeasurementSinkMock.hpp>

namespace Testing {

class ISensorMock : public ISensor {
public:
    ISensorMock(IMeasurementSinkMock& sink, int targetInterval, char* key) : ISensor(sink, targetInterval, key) { }

    MOCK_METHOD0(run, void());
    MOCK_METHOD0(getKeyword, char*());
    MOCK_METHOD1(setKeyword, void(char* keyword));
};

} // namespace Testing

#endif // ISENSOR_MOCK_HPP_
