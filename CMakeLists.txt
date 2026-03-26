cmake_minimum_required(VERSION 3.20)

project(IoT_Simulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_subdirectory(libs/algorithms)

add_executable(iot_sim_app
    src/main.cpp
    src/device.cpp
    src/weatherSim.cpp
    src/csv_manager.cpp

    src/Passive/thermometer.cpp
    src/Passive/windowSensor.cpp
    src/Passive/soilHumiditySensor.cpp
    src/Passive/higrometer.cpp
    src/Passive/doorSensor.cpp
    src/Passive/airQualitySensor.cpp
    src/Passive/barometer.cpp
    src/Passive/lightSensor.cpp
    src/Passive/pir.cpp
    src/Passive/rainSensor.cpp

    src/Active/waterPump.cpp
    src/Active/socket.cpp
    src/Active/lock.cpp
    src/Active/heater.cpp
    src/Active/conditioning.cpp
    src/Active/bulb.cpp
)   

target_include_directories(iot_sim_app PRIVATE
                        ${CMAKE_CURRENT_SOURCE_DIR}/inc
                        ${CMAKE_CURRENT_SOURCE_DIR}/inc/Passive
                        ${CMAKE_CURRENT_SOURCE_DIR}/inc/Active
)

target_link_libraries(iot_sim_app PRIVATE algorithms)

# TESTS
enable_testing()
find_package(GTest REQUIRED)
add_executable(test_stack
                tests_unit/test_stack.cpp
)

target_link_libraries(test_stack PRIVATE
    algorithms
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME StackTest COMMAND test_stack)