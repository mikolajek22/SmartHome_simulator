#include <filesystem>
#include <format>

#include "csv_manager.h"


const string header = "date,time,temperature,airQuality,pressure,humidity,light,rain,rainIntensity,soilHumidity";

string dateToString(uint16_t y, uint8_t m, uint8_t d);
string timeToString(uint8_t h, uint8_t m, uint8_t s);

void CSV_Manager::openFile(string path)
{
    bool createHeader = false;  // no header || file does not exist
    bool truncate = false;      // depracted file
    cout << "Opening file: " << path << endl;
    /* Check if file exists */
    if (!filesystem::exists(path))
    {
        createHeader = true;
    }
    
    else 
    {
        /* File exists - validate header (name of columns)*/
        ifstream validate(path);
        string firstRow;
        getline(validate,firstRow);

        if (firstRow != header)
        {
            createHeader = true;
            truncate = true;
        }
        validate.close();
    }

    /* Open with proper attribute */
    if (truncate) file.open(path);
    else file.open(path,ios::app);

    
    if (!file.is_open())
    {
        cout <<"Failed to open file!" << endl;
    }

    if (createHeader)
    {
        file << header << "\n";
    }

}

void CSV_Manager::closeFile()
{
    if (file.is_open())
    {
        file.close();
    }
}

void CSV_Manager::AddRow(Date &date, WeatherSim &simulator)
{
    if (!file.is_open())
    {
        return;
    }
    string tmpString = dateToString(date.year, date.month, date.day);
    file << tmpString << ",";

    tmpString = timeToString(date.hour, date.minute, date.second);
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getTemperature());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getAirQuality());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getPressure());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getHumidity());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getLight());
    file << tmpString << ",";

    tmpString = format("{}", simulator.getRain());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getRainIntensity());
    file << tmpString << ",";

    tmpString = format("{:.2f}", simulator.getSoilHumidity());
    file << tmpString << ",";

    file << "\n";
}

string dateToString(uint16_t y, uint8_t m, uint8_t d)
{
    return format("{:04}/{:02}/{:02}", y, m, d);
}

string timeToString(uint8_t h, uint8_t m, uint8_t s)
{
    return format("{:02}/{:02}/{:02}", h, m, s);
}