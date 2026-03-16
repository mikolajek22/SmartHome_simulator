
#include <iostream>
#include <thread>
#include <chrono>
#include "thermometer.h"
#include "weatherSim.h"
#include "csv_manager.h"

int main()
{
    uint8_t mac1[MAC_SIZE] = {0x10,0x20,0x30,0x40,0x50,0x01};

    Thermometer t1(mac1, 0xC0A80002, 0xFFFFFF00, 0xC0A80001);

    // while (true)
    // {
        t1.simulate();

        std::time_t now = std::time(nullptr);

        std::cout << "Time: " << now
                  << " Temp: " << t1.getTemperature()
                  << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    Date date = {
        .second =0,
        .minute = 0,
        .hour = 0,
        .day = 1,
        .month = 1,
        .year = 2026
    };

    Date endDate = {
        .second =0,
        .minute = 0,
        .hour = 10,
        .day = 1,
        .month = 1,
        .year = 2026
    };

    WeatherSim simulator(date, endDate);

    while (!(date == endDate))
    {
        date = simulator.simulateSingleHour();
    }


    CSV_Manager csv_man;
    csv_man.openFile("../data/test.txt");
    

}
