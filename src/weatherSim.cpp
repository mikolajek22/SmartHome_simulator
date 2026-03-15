
#include "weatherSim.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <numbers>


#define NUMBER_OF_DAYS 365
#define HOURS_PER_DAY 24
#define HOUR_OF_MAX_TEMP 14

const float pi = 3.1415926f;


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