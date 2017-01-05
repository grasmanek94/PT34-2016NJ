set (INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set (INCLUDE_DIR_LL "${INCLUDE_DIR}/SmartBeeHive")
set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")


include_directories(${INCLUDE_DIR}
                    ${CONFIG_DIR}
                   )

set(SOURCE
    "${SOURCE_DIR}/BeehiveMeasurementUnit.cpp"
    "${SOURCE_DIR}/Measurement.cpp"
   )


set(HEADER
    "${INCLUDE_DIR_LL}/BeehiveMeasurementUnit.hpp"
    "${INCLUDE_DIR_LL}/ISensor.hpp"
    "${INCLUDE_DIR_LL}/IMeasurementSink.hpp"
    "${INCLUDE_DIR_LL}/Measurement.hpp"
    "${INCLUDE_DIR_LL}/Testing/SensorMock.hpp"
    "${INCLUDE_DIR_LL}/Testing/MeasurementSinkMock.hpp"
   )

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})

# compile with C++ 11
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -std=c++11)
