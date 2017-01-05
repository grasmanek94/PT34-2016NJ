#ifndef IMEASUREMENTSINK_MOCK_HPP_
#define IMEASUREMENTSINK_MOCK_HPP_

#include "gmock/gmock.h"
#include <SmartBeeHive/IMeasurementSink.hpp>

namespace Testing {

class IMeasurementSinkMock : public IMeasurementSink {
 public:
  MOCK_METHOD1(sendMeasurement, void(Measurement measurement));
};

} // namespace Testing

#endif // IMEASUREMENTSINK_MOCK_HPP_
