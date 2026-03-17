#pragma once

#include <iostream>
#include <fstream>

#include "weatherSim.h"

using namespace std;

class CSV_Manager {
    public:

        void openFile(string path);
        void closeFile();
        void writeFile();
        void AddRow(Date &date, WeatherSim &simulator);
    private:
        ofstream file; 
};
