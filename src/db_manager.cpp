#include "db_manager.h"

#include <iostream>
#include <format>
#include <sqlite3.h>

DatabaseManager::DatabaseManager() :
    db(nullptr)
{

}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open(string path)
{
    if (sqlite3_open(path.c_str(), &db))
    {
        cout << "Failed to open database!" << endl;
        return false;
    }

    cout << "Database opened successfully" << endl;

    return true;
}

void DatabaseManager::close()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::execute(const string& sql)
{
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db,
                          sql.c_str(),
                          nullptr,
                          nullptr,
                          &errMsg);

    if (rc != SQLITE_OK)
    {
        cout << "SQL Error: " << errMsg << endl;

        sqlite3_free(errMsg);

        return false;
    }

    return true;
}

bool DatabaseManager::insertWeatherData(Date& date,
                                        WeatherSim& sim)
{
    sqlite3_stmt* stmt;

    string timestamp =
        format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
               date.year,
               date.month,
               date.day,
               date.hour,
               date.minute,
               date.second);

    const char* sql =
        "INSERT INTO weather_data ("
        "timestamp,"
        "temperature,"
        "air_quality,"
        "pressure,"
        "humidity,"
        "light,"
        "rain,"
        "rain_intensity,"
        "soil_humidity"
        ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    int rc = sqlite3_prepare_v2(db,
                                sql,
                                -1,
                                &stmt,
                                nullptr);

    if (rc != SQLITE_OK)
    {
        std::cout << "Prepare failed: "
          << sqlite3_errmsg(db)
          << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1,
                      timestamp.c_str(),
                      -1,
                      SQLITE_TRANSIENT);

    sqlite3_bind_double(stmt, 2,
                        sim.getTemperature());

    sqlite3_bind_double(stmt, 3,
                        sim.getAirQuality());

    sqlite3_bind_double(stmt, 4,
                        sim.getPressure());

    sqlite3_bind_double(stmt, 5,
                        sim.getHumidity());

    sqlite3_bind_double(stmt, 6,
                        sim.getLight());

    sqlite3_bind_int(stmt, 7,
                     sim.getRain());

    sqlite3_bind_double(stmt, 8,
                        sim.getRainIntensity());

    sqlite3_bind_double(stmt, 9,
                        sim.getSoilHumidity());

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE)
    {
        cout << "Insert failed!" << endl;
        return false;
    }

    return true;
}