
#include "weatherSim.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <numbers>
#include <iostream>

#define NUMBER_OF_DAYS 365
#define HOURS_PER_DAY 24
#define HOUR_OF_MAX_TEMP 14

const float pi = 3.1415926f;

bool isLapYear(uint16_t year);
uint16_t dayOfYear(const Date &d);
void nextDay(Date &d);


float randf(float min, float max)
{
    return min + (max - min) * (float(rand()) / float(RAND_MAX));
}

WeatherSim::WeatherSim()
{
    dayIdx = 0;
}

WeatherSim::WeatherSim(Date (&start), Date (&end)) : date(start), endDate(end)
{
    dayIdx = 0;
}

/**
 * @brief temperature from -10 C to +30 C (depends on hour and season of the year). Amplitude is 20 Deg
 */
float WeatherSim::simulateTemperature()
{
    
    
    /* Season */
    float seasonal = 20.0f * sin((2.0f * pi * dayIdx / NUMBER_OF_DAYS) - pi/2.0f) + 10.0f;
    
    /* Daily (max temp at 2:00 PM)*/
    float daily = 5.0f * sin(2.0f * pi * (date.hour - HOUR_OF_MAX_TEMP) / HOURS_PER_DAY);

    /* Random factor */
    float noise = randf(-2.0f, 2.0f);

    float temp = seasonal + daily + noise;

    if (rain) temp -= 2.0f;

    if (temp > 30.0) temp = 30.0;
    if (temp < -10.0) temp = -10.0;

    temperature = temp;
    return temp;
}

float WeatherSim::simulateAirQuality()
{
    float winter = 30.0f * (1.0f - sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS));

    airQuality = 30.0f + winter;

    if (rain) airQuality -= 20.0f;

    airQuality += randf(-5.0f, 5.0f);

    if (airQuality < 5.0f) airQuality = 5.0f;
    if (airQuality > 200.0f) airQuality = 200.0f;

    return airQuality;
}
float WeatherSim::simulatePressure()
{
    float seasonal = 6.0f * sin(2.0f * pi* dayIdx / NUMBER_OF_DAYS);
    float daily = 1.0f * sin(2.0f * pi* date.hour / HOURS_PER_DAY);
    float noise = randf(-3.0f, 3.0f);

    pressure = 1013.0f + seasonal + daily + noise;
    if (pressure < 980.0f) pressure = 980.0f;
    if (pressure < 1040.0f) pressure = 1040.0f;

    return pressure;
}
float WeatherSim::simulateHumidity()
{
    humidity = 70.0f;

    if (temperature > 25.0f) humidity -= 20.0f;

    if (rain) humidity += 25.0f;

    humidity += randf(-10.0f, 10.0f);

    if (humidity > 100.0f) humidity = 100.0f;
    if (humidity < 20.0f) humidity = 20.0f;

    return humidity;
}

float WeatherSim::simulateSoilHumidity()
{
    if (rain) soilHumidity += rainIntensity * 0.8f;

    // NOTE: validate if it is not too fast - maybe it should be dependent from temperature also.
    float evaporation = light / 1200.0f;
    soilHumidity -= evaporation;

    if (soilHumidity > 100.0f) soilHumidity = 100.0f;
    if (soilHumidity < 0.0f) soilHumidity = 0.0f;

    return soilHumidity;
}

bool WeatherSim::simulateRain()
{
    if (rainHoursRemaining > 0)
    {
        rainHoursRemaining--;
        rain = true;
        return rain;
    }
    // season from 0.1 to to 0.6
    float seasonal = 0.25f * sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS - pi / 2.0f) + 0.35f;

    float propability = seasonal;

    if (pressure > 1005.0f) propability += 0.25f;
    if (humidity > 80.0f) propability += 20.0f;

    float r = randf(0.0f, 1.0f);

    if (propability > r)
    {
        rainHoursRemaining = randf(3,12);
        rain = true;
        return rain;
    }

    rain = false;
    return rain;
}

float WeatherSim::simulatRainIntensity() {
    if (!rain) {
        rainIntensity = 0.0f;
        return rainIntensity;
    }

    rainIntensity = randf(0.2f, 4.0f);

    if (humidity > 0.90f) rainIntensity += randf(2.0f, 5.0f);
    
    return rainIntensity;
}

float WeatherSim::simulatLight()
{
    /* from (0:00 AM, 0) -> (12:00 AM, 1) -> (12:00 PM, 0) */
    float dayLight = sin(pi * date.hour / HOURS_PER_DAY);
    if (dayLight < 0.0f) dayLight = 0.0f;

    float seasonal = 0.6f + 0.4f * sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS);
    light = 1000.0f * dayLight * seasonal;

    if (rain) light *=0.3f;

    return light;
}

void WeatherSim::updateWeather() {
    simulatePressure();
    simulateTemperature();
    simulateHumidity();
    simulateRain();
    simulatRainIntensity();
    simulatLight();
    simulateSoilHumidity();
    simulateAirQuality();
}

Date WeatherSim::simulateSingleHour()
{
    Date actDate = date;
    dayIdx = dayOfYear(date);
    updateWeather();
    std::cout << "Performing Simulation for "
          << int(date.day) << "/"
          << int(date.month) << "/"
          << date.year << " : "
          << int(date.hour) << ":"
          << int(date.minute) << ":"
          << int(date.second)
          << std::endl;
    date.hour++;
    if (date.hour > 23)
    {
        date.hour = 0;
        nextDay(date);
    }
    return actDate;
}

static const uint8_t daysOfMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


bool isLapYear(uint16_t year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

uint16_t dayOfYear(const Date &d)
{
    uint16_t day = 0;
    for (uint8_t i = 1; i < d.month; i++)
    {
        day += daysOfMonths[i - 1];

        if (i == 2 && isLapYear(d.year))
        {
            day+=1;
        }
    }
    day += d.day;
    return day;
}

void nextDay(Date &d)
{
    uint8_t days = daysOfMonths[d.month - 1];
    if (d.month == 2 && isLapYear(d.year))
    {
        days = 29;
    }
    d.day++;

    if (d.day > days)
    {
        d.day = 1;
        d.month++;
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
}