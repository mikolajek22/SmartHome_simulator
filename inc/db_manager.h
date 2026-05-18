#pragma once

#include <string>
#include <sqlite3.h>

#include "weatherSim.h"

using namespace std;

class DatabaseManager
{
    public:
        DatabaseManager();
        ~DatabaseManager();

        bool open(string path);
        void close();

        bool execute(const string& sql);

        bool insertWeatherData(Date& date,
                               WeatherSim& sim);

    private:
        sqlite3* db;
};