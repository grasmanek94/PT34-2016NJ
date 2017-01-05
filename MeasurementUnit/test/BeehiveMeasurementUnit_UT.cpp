#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <SmartBeeHive/Testing/ISensorMock.hpp>
#include <SmartBeeHive/BeehiveMeasurementUnit.hpp>

using namespace testing;

///@todo Design an interface for timesources so those can be mocked

TEST(BeehiveMeasurementTest, executeSensor)
{
    Testing::IMeasurementSinkMock sink;
    char keyword[255] = "mock sensor";

    Testing::ISensorMock sensor(sink, 100, keyword);
    BeehiveMeasurementUnit beehive(1, &sensor);

    EXPECT_CALL(sensor, run());

    beehive.init();

    ASSERT_TRUE(beehive.status());

    beehive.run();
}
