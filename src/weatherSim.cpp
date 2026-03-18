
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

WeatherSim::WeatherSim(Date (&start), Date (&end)) : date(start), endDate(end), 
                        pressure(1013.0f), temperature(-10.0f), humidity(70.0f), 
                        soilHumidity(50.0f), rainHoursRemaining(0)
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
    float noise = randf(-6.0f, 6.0f);

    float temp = seasonal + daily + noise;

    if (rain) temp -= 2.0f;

    if (temp > 30.0) temp = 30.0;
    if (temp < -10.0) temp = -10.0;

    // temperature = temp;
    temperature = 0.8f * temperature + 0.2f * temp;
    return temperature;
}

float WeatherSim::simulateAirQuality()
{
    float winter = 30.0f * (1.0f - sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS - pi/2));

    airQuality = 30.0f + winter;

    if (rain) airQuality -= 20.0f;

    airQuality += randf(-5.0f, 5.0f);

    if (airQuality < 5.0f) airQuality = 5.0f;
    if (airQuality > 200.0f) airQuality = 200.0f;

    return airQuality;
}
float WeatherSim::simulatePressure()
{
    float newPressure = 0;
    float seasonal = 2.0f * sin(2.0f * pi* dayIdx / NUMBER_OF_DAYS);
    float daily = 0.5f * sin(2.0f * pi* date.hour / HOURS_PER_DAY);
    float noise = randf(-1.0f, 1.0f);

    newPressure = 1013.0f + seasonal + daily + noise;
    newPressure += randf(-20.0f, 20.0f);
    if (newPressure < 980.0f) newPressure = 980.0f;
    if (newPressure > 1040.0f) newPressure = 1040.0f;

    pressure = 0.95f * pressure + 0.05f * newPressure;
    
    return pressure;
}
float WeatherSim::simulateHumidity()
{
    static float prevHumidity = 0;
    humidity = 70.0f;

    if (temperature > 25.0f) humidity -= 20.0f;

    if (rain) humidity += 15.0f;

    humidity += randf(-10.0f, 10.0f);

    if (humidity > 100.0f) humidity = 100.0f;
    if (humidity < 20.0f) humidity = 20.0f;

    if (prevHumidity)
        humidity = 0.8f * humidity + 0.2f * prevHumidity;
    prevHumidity = humidity;
    return humidity;
}

float WeatherSim::simulateSoilHumidity()
{
    float newHumidity = humidity;
    if (rain) 
    {
        float rainFactor = std::min(rainIntensity, 5.0f);
        newHumidity += rainFactor * 0.7;
    }
    

    // NOTE: validate if it is not too fast - maybe it should be dependent from temperature also.
    float evaporation = (light / 10000.0f) + (temperature > 25.0f ? 0.3f : 0.0f);
    newHumidity -= evaporation;

    newHumidity *= 0.995f;
    
    if (newHumidity > 100.0f) newHumidity = 100.0f;
    if (newHumidity < 0.0f) newHumidity = 0.0f;
    soilHumidity = 0.9f * soilHumidity + 0.1f * newHumidity;
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
    if (date.hour != 0) 
    {
        rain = false;
        return false;
    }
    // season from 0.1 to to 0.6
    float seasonal = 0.1f * sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS - pi / 2.0f) + 0.16f;

    float propability = seasonal;

    if (pressure < 1005.0f) propability += 0.15f;
    if (humidity > 80.0f) propability += 0.10f;

    if (propability > 0.7f) propability = 0.7f;
    if (propability < 0.0f) propability = 0.0f;

    float r = randf(0.0f, 1.0f);

    if (propability > r)
    {
        rainHoursRemaining = randf(12,72);
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

    // rainIntensity = randf(0.0f, 2.0f);

    // // randomly big intesity
    // if (randf(0.0f,1.0f) < 0.2f) rainIntensity += randf(2.0f, 5.0f);

    float r = randf(0.0f, 1.0f);

    if (r < 0.8f)
        rainIntensity = randf(0.0f, 1.0f);  //soft rain
    else if (r < 0.9f)
        rainIntensity = randf(1.0f, 3.0f);   // med rain
    else
        rainIntensity = randf(3.0f, 8.0f);   // big rain

    if (humidity > 90.0f) rainIntensity += randf(1.0f, 2.0f);
    
    return rainIntensity;
}

float WeatherSim::simulatLight()
{
    /* from (0:00 AM, 0) -> (12:00 AM, 1) -> (12:00 PM, 0) */
    float dayLight = sin(pi * date.hour / HOURS_PER_DAY);
    if (dayLight < 0.0f) dayLight = 0.0f;

    float seasonal = 0.6f + 0.4f * sin(2.0f * pi * dayIdx / NUMBER_OF_DAYS - pi/2);
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