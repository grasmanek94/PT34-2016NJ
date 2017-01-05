#ifndef MEASUREMENTSINK_MOCK_HPP_
#define MEASUREMENTSINK_MOCK_HPP_

#include "gmock/gmock.h"
#include <SmartBeeHive/IMeasurementSink.hpp>

namespace Testing {

class MeasurementSinkMock : public IMeasurementSink {
 public:
  MOCK_METHOD1(sendMeasurement, void(Measurement measurement));
};

} // namespace Testing

#endif // MEASUREMENTSINK_MOCK_HPP_
