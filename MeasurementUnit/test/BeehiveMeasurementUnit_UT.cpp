#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <SmartBeeHive/Testing/ISensorMock.hpp>
#include <SmartBeeHive/BeehiveMeasurementUnit.hpp>

using namespace testing;
using namespace Testing;

TEST(BeehiveMeasurementTest, executeSensor)
{
    MeasurementSinkMock sink;

    char keyword1[255] = "mock sensor 1";
    SensorMock sensor1(sink, 100, keyword1);

    char keyword2[255] = "mock sensor 2";
    SensorMock sensor2(sink, 100, keyword2);

    SensorMock* sensors[] = {&sensor1, &sensor2};

    BeehiveMeasurementUnit beehive(2, (ISensor**)sensors);

    EXPECT_CALL(sensor1, run());
    EXPECT_CALL(sensor2, run());

    beehive.init();

    ASSERT_TRUE(beehive.status());

    beehive.run();
}
