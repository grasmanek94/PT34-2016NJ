include(GoogleTest.cmake)

set(EXECUTABLE_NAME "${PROJECT_NAME}_UT")

set(TEST_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/BeehiveMeasurementUnit_UT.cpp"
)


set(TEST_LINK_LIB
        ${GTEST_LIB_LOCATION}
        ${GMOCK_LIB_LOCATION}
	${GMOCK_MAIN_PATH}
        pthread
   )

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/include"
)

add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE})
target_link_libraries(${EXECUTABLE_NAME} ${TEST_LINK_LIB} ${PROJECT_NAME})
add_dependencies(${EXECUTABLE_NAME} gtest_external)

# compile with C++ 11
set_target_properties(${EXECUTABLE_NAME} PROPERTIES COMPILE_FLAGS -std=c++11)

