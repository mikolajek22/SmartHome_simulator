cmake_minimum_required(VERSION 3.20)

project(IoT_Simulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc
                    inc/Passive
                    inc/Active
)


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

