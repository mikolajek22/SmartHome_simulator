#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class CSV_Manager {
    public:

        void openFile(string path);
        void closeFile();
        void writeFile();
        void AddRow();
    private:
        ofstream file; 
};
