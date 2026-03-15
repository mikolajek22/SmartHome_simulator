#pragma once

#include <stdint.h>

struct Date {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

class WeatherSim {
    public:
        WeatherSim();
        WeatherSim(Date (&start), Date (&end));

        void updateWeather();
        

    private:

        /* Day of the year */
        uint16_t dayIdx = 0;

        Date date;
        Date endDate;

        bool rain;
        uint8_t rainHoursRemaining;
        float rainIntensity;

        float temperature;
        float humidity;
        float soilHumidity;
        float pressure;
        float light;
        float airQuality;


        float simulateTemperature();
        float simulateAirQuality();
        float simulatePressure();
        float simulateHumidity();
        float simulateSoilHumidity();
        bool simulateRain();
        float simulatRainIntensity();
        float simulatLight();

};